#PROG: cgcedit
#cgcedit: --output-mach k1om
#source: empty.s
#as: --64
#readcgc: -h
#name: Update CGC header 4
#target: x86_64-*-*

#...
CGC Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             CGC64
  Data:                              2's complement, little endian
  Version:                           1 \(current\)
#...
  Machine:                           Intel K1OM
#...
