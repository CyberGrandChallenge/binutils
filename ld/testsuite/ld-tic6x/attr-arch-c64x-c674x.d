#name: C6X arch attribute merging, c64x c674x
#as: -mlittle-endian
#ld: -r -mcgc32_tic6x_le
#source: attr-arch-c64x.s
#source: attr-arch-c674x.s
#readcgc: -A

Attribute Section: c6xabi
File Attributes
  Tag_ISA: C674x
