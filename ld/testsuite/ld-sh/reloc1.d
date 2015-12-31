#source: reloc1.s
#as: -big
#ld: -shared -EB --defsym foo=0x9000
#objdump: -sj.data
#target: sh*-*-cgc sh-*-vxworks

.*:     file format cgc32-sh.*

Contents of section \.data:
 .* 9123 .*
