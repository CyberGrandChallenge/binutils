#source: stolib.s
#as: --abi=32 --isa=SHmedia
#ld: -shared -mshcgc32
#objdump: -drj.text
#target: sh64-*-cgc

.*: +file format cgc32-sh64.*

#pass
