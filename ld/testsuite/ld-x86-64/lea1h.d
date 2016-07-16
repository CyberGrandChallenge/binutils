#source: lea1.s
#as: --64
#ld: -pie -mcgc_x86_64
#readcgc: -Sw

#failif
#...
[ 	]*\[.*\][ 	]+.*\.got .*
#...
