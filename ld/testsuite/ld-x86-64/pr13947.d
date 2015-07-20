#ld: -shared --emit-relocs
#readcgc: -S --wide

#failif
#...
 +\[ [0-9]\] .rela.rela.plt +RELA +[0-9a-f]+ +[0-9a-f]+ 0+ +.*
#...
