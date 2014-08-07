#ld: --shared -mcgc_i386
#readcgc: -S --wide
#as: --32

#...
[ 	]*\[.*\][ 	]+\.dynamic[ 	]+DYNAMIC.*
[ 	]*\[.*\][ 	]+.*STRTAB.*
#pass
