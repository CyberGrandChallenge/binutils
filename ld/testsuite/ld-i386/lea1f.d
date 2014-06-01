#source: lea1.s
#as: --32
#ld: -mcgc_i386
#readcgc: -Sw

#failif
#...
[ 	]*\[.*\][ 	]+.*\.got .*
#...
