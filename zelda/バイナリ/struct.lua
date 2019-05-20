
fd = xedit.struct_create("abc")
xedit.struct_add_member(fd, "int,name")
xedit.struct_add_member(fd, "int,type")
xedit.struct_add_member(fd, "char,data[8],char")
res = xedit.struct_close(fd)

print(res)
