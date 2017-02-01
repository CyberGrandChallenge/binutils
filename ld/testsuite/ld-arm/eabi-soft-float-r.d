#source: eabi-soft-float.s
#as:
#ld: -r
#readcgc: -h
# This test is only valid on CGC based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*
# if we call "ld -r", it should *not* set either of the float ABI flags

CGC Header:
#...
  Flags:                             0x5000000, Version5 EABI
#...
