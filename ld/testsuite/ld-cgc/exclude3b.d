#source: exclude3.s
#ld: --shared
#readcgc: -S --wide
#target: *-*-linux* *-*-gnu*

#failif
#...
[ 	]*\[.*\][ 	]+\.foo1[ 	]+.*
#...
