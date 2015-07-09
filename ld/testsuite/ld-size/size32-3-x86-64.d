#source: size32-3a.s
#source: size32-3b.s
#as: --64
#ld: -shared -mcgc_x86_64 -z nocombreloc
#readcgc: -r --wide
#target: x86_64-*-*

#failif
#...
.* +R_X86_64_NONE +.*
#...
