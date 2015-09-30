#source: size32-3a.s
#source: size32-3b.s
#as: --32
#ld: -shared -mcgc_i386 -z nocombreloc
#readcgc: -r --wide
#target: x86_64-*-* i?86-*-*

#failif
#...
.* +R_386_NONE +.*
#...
