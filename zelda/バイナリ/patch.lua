--
-- xedit.exe 用 Luaスクリプトサンプル
--
-- 下記の様なパッチ情報を記述したファイルからパッチを行う
--
-- 00000030: 30 31 32 33  → FF FF FF FF
-- 00000040: 40 41 42 43 44 → FF FF FF FF FF
-- 00000050: 50 51 52 →  FF FF FF
--

--[[* split string *]]--
-- return iterator
string.split_it = function(str, sep)
	if str == nil then return nil end
	assert(type(str) == "string", "str must be a string")
	assert(type(sep) == "string", "sep must be a string")
	return string.gmatch(str, "[^\\" .. sep .. "]+")
end

-- return table
string.split = function(str, sep)
	local ret = {}
	for seg in string.split_it(str, sep) do
		ret[#ret+1] = seg
	end
	return ret
end

function xedit_patch(add, old, new, chk)
	res = (xedit.get(add) == old)
	if res then
		if (not chk) then
			xedit.set(add, new)
			print(string.format(
				"patch %08x: %02x -> %02x ... OK", add, old, new))
		end
	else
		print(string.format("patch %08x: %02x ~= %02x ... NG",
			add, xedit.get(add), old))
	end
	return res
end

function patch(address, old_str, new_str, chk)
	function create_table(data)
		local tbl = {}
		for num in string.gmatch(data, "(%x+)%s*")
		do
			numi = tonumber(num, 16);
			if (numi == nil) then numi = 0 end
			table.insert(tbl, numi)
		end
		return tbl
	end
	
	assert(type(address) == "string", "address must be a string")
	assert(type(old_str) == "string", "old_str must be a string")
	assert(type(new_str) == "string", "new_str must be a string")

	ret = false
	add = tonumber(address, 16)
	if (add == nil) then return ret end
	old_data = create_table(old_str)
	new_data = create_table(new_str)

	if (#old_data == 0) then return ret end
	if (#old_data == #new_data) then
		for index = 1, #old_data
		do
			if (xedit ~= nil) then
				ret = xedit_patch(add, old_data[index], new_data[index], chk)
			else
				ret = false
				if (chk) then
					print(string.format(
						"%08x %02x %02x", add, old_data[index], new_data[index]))
				end
			end
			add = add + 1
		end
	end
	return ret
end

if (#arg == 2) then
	file = arg[2]
else
	-- GUI処理用要求
	ret, file = wui.input("パッチファイルを指定して下さい")
	assert(ret, "Exit")
end

-- 処理対象ファイル名出力
print("Target: " .. file)

-- パッチ元ネタ
for line in io.lines(file)
do
	print("// " .. line)
end

-- パッチチェック
result = true
for line in io.lines(file)
do
	ptable = line:split(":→")
	if (#ptable == 3) then
		result = patch(ptable[1], ptable[2], ptable[3], true) and result
	end
end

-- パッチ
if (result) then
	for line in io.lines(file)
	do
		ptable = line:split(":→")
		if (#ptable == 3) then
			patch(ptable[1], ptable[2], ptable[3], false)
		end
	end
end
