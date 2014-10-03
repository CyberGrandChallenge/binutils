#source: ifunc-14b.s
#source: ifunc-14a.s
#ld: -shared -z nocombreloc
#readcgc: -d
#target: aarch64*-*-*

#failif
#...
.*\(TEXTREL\).*
#...
