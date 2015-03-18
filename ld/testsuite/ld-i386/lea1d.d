#source: lea1.s
#as: --32
#ld: -Bsymbolic -shared -mcgc_i386
#readcgc: -Sw

#failif
#...
[ 	]*\[.*\][ 	]+.*\.got .*
#...
