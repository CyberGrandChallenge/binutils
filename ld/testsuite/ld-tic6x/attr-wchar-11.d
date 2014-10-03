#name: C6X wchar_t attribute merging, 1 1
#as: -mlittle-endian
#ld: -r -mcgc32_tic6x_le
#source: attr-wchar-1.s
#source: attr-wchar-1.s
#readcgc: -A

Attribute Section: c6xabi
File Attributes
  Tag_ISA: C674x
  Tag_ABI_wchar_t: 2 bytes
