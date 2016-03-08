#source: eabi-soft-float.s
#as:
#ld: -r
#readcgc: -h
# This test is only valid on CGC based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*
# if we compile for EABI ver4, ld should *not* set either of the float ABI flags

CGC Header:
#...
  Flags:                             0x4000000, Version4 EABI
#...
