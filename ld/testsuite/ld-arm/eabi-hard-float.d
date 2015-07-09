#source: eabi-hard-float.s
#as:
#ld: -r
#readcgc: -h
# This test is only valid on CGC based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*
# Check that we set the hard-float ABI flag directly

CGC Header:
#...
  Flags:                             0x5000400, Version5 EABI, hard-float ABI
#...
