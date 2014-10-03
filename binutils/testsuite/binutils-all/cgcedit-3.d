#PROG: cgcedit
#cgcedit: --output-osabi FenixOS
#source: empty.s
#readcgc: -h
#name: Update CGC header 3
#target: *-*-linux* *-*-gnu*

#...
CGC Header:
  Magic:   7f 45 4c 46 .*
#...
  Version:[ \t]+1 \(current\)
#...
  OS/ABI:[ \t]+FenixOS
#...
