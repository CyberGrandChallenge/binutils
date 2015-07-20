#source: unknown2.s
#ld: -shared
#readcgc: -S
#target: *-*-linux* *-*-gnu*

#...
  \[[ 0-9]+\] \.note.foo[ \t]+NOTE[ \t]+.*
#pass
