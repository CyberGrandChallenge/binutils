#PROG: cgcedit
#cgcedit: --output-type exec
#source: empty.s
#readcgc: -h
#name: Update CGC header 2
#target: *-*-linux* *-*-gnu*

#...
CGC Header:
  Magic:   7f 45 4c 46 .*
#...
  Version:[ \t]+1 \(current\)
#...
  Type:[ \t]+EXEC \(Executable file\)
#...
