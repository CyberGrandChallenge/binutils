#source: exclude3.s
#ld: -r
#readcgc: -S --wide

#...
[ 	]*\[.*\][ 	]+\.foo1[ 	]+PROGBITS.*[ 	]+E[   ]+.*
#pass
