#source: attr-merge-unknown-2.s
#source: blank.s
#as:
#ld:
#warning: Unknown EABI object attribute 82
#readcgc: -A
# This test is only valid on CGC based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*

Attribute Section: aeabi
File Attributes
  Tag_ARM_ISA_use: Yes
  Tag_THUMB_ISA_use: Thumb-1
