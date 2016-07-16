#source: lea1.s
#as: --32
#ld: -pie -mcgc_i386
#readcgc: -Sw

#failif
#...
[ 	]*\[.*\][ 	]+.*\.got .*
#...
