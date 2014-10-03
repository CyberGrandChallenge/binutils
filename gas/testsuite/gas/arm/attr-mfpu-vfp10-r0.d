# name: attributes for -mfpu=vfp10-r0
# source: blank.s
# as: -mfpu=vfp10-r0
# readcgc: -A
# This test is only valid on EABI based ports.
# target: *-*-*eabi* *-*-nacl*

Attribute Section: aeabi
File Attributes
  Tag_ARM_ISA_use: Yes
  Tag_THUMB_ISA_use: Thumb-1
  Tag_FP_arch: VFPv1
