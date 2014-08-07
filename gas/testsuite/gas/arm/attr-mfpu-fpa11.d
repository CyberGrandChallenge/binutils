# name: attributes for -mfpu=fpa11
# source: blank.s
# as: -mfpu=fpa11
# readcgc: -A
# This test is only valid on EABI based ports.
# target: *-*-*eabi* *-*-nacl*

Attribute Section: aeabi
File Attributes
  Tag_ARM_ISA_use: Yes
  Tag_THUMB_ISA_use: Thumb-1
