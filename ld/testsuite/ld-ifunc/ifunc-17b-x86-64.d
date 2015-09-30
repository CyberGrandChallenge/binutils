#source: ifunc-17b.s
#source: ifunc-17a.s
#ld: -static -m cgc_x86_64
#as: --64
#readcgc: -s --wide
#target: x86_64-*-*

#...
 +[0-9]+: +[0-9a-f]+ +4 +OBJECT +GLOBAL +DEFAULT +[1-9] foo
#pass
