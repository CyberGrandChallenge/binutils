#source: lea1.s
#as: --x32
#ld: -mcgc32_x86_64
#readcgc: -Sw

#failif
#...
[ 	]*\[.*\][ 	]+.*\.got .*
#...
