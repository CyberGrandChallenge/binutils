#ld: --shared -mcgc_x86_64
#readcgc: -S --wide
#as: --64

#...
[ 	]*\[.*\][ 	]+\.dynamic[ 	]+DYNAMIC.*
[ 	]*\[.*\][ 	]+.*STRTAB.*
#pass
