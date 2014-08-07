#source: lea1.s
#as: --x32
#ld: -Bsymbolic -shared -mcgc32_x86_64
#readcgc: -Sw

#failif
#...
[ 	]*\[.*\][ 	]+.*\.got .*
#...
