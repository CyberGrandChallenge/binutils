#name: C6X array attribute merging, 16 816
#as: -mlittle-endian
#ld: -r -mcgc32_tic6x_le
#source: attr-array-16.s
#source: attr-array-816.s
#readcgc: -A

Attribute Section: c6xabi
File Attributes
  Tag_ISA: C674x
  Tag_ABI_array_object_alignment: 16-byte
  Tag_ABI_array_object_align_expected: 16-byte
