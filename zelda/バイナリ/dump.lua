--
-- xedit.exe 用 Luaスクリプトサンプル
--
-- データのダンプ表示(16, 10, 8, 2進)を行う
--

function hex2bin(data)
	bit = 0x80
	ret = ""
	while (bit ~= 0)
	do
		x, y = math.modf(data / bit)
		if (x == 1) then
			ret = ret .. "1"
			data = data - bit
		else
			ret = ret .. "0"
		end
		bit = math.modf(bit / 2)
	end
	return ret
end

size = xedit.size()
for i = 1, size
do
	data = xedit.get(i - 1)
	if (i == 1) then
		print(" address,HEX, DEC, OCT, BIN")
	end
	print(string.format("%08x, %02x, %3d, %3o, %s",
						i - 1, data, data, data, hex2bin(data)))
end

