#source: ifunc-14a.s
#source: ifunc-14c.s
#source: ifunc-14b.s
#ld: -shared -m cgc_i386 -z nocombreloc
#as: --32
#readcgc: -r --wide
#target: x86_64-*-* i?86-*-*

#failif
#...
.* +R_386_NONE +.*
#...
