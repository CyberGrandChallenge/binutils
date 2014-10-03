#source: eabi-soft-float.s
#as:
#ld: -r
#readcgc: -h
# This test is only valid on CGC based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*
# Check that we set the soft-float ABI flag directly

CGC Header:
#...
  Flags:                             0x5000200, Version5 EABI, soft-float ABI
#...
