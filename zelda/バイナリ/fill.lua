--
-- xedit.exe 用 Luaスクリプトサンプル
--
-- ビッグエンディアン 4 バイトで 0x00 ～ 0xff 番地までを
-- インクリメント値で埋めるつくす
--
-- usage : fill.lua [start size [data]]
--

function ins_b4(addr, val)
	xedit.set(addr + 3, val)
	xedit.set(addr + 2, val / 0x100)
	xedit.set(addr + 1, val / 0x10000)
	xedit.set(addr + 0, val / 0x1000000)
end

if (#arg >= 3) then
	data = tonumber(arg[3], 16);
else
	data = 0
end

if (#arg >= 2) then
	start = tonumber(arg[1], 16);
	len = tonumber(arg[2], 16);
else
	start = 0
	len = 0xff
end

print(string.format("fill start = %x, len = %x, initval = %x",
						start, len, data))
for addr = start, start + len, 4
do
	ins_b4(addr, data)
	print(string.format("addr = 0x%02x, data = 0x%02x",
							addr, data))
	data = data + 1
end
print(string.format("size = 0x%x", xedit.size()))
