#source: refdbglib.s
#as: -little
#ld: -shared -EL
#objdump: -dr
#target: sh*-*-linux* sh*-*-netbsd*

.*: +file format cgc32-sh.*

#pass
