#source: compress1.s
#as: --compress-debug-sections
#ld: -r
#readcgc: -S --wide

#failif
#...
  \[[ 0-9]+\] \.zdebug_.*[ 	]+(PROGBITS|MIPS_DWARF)[ 	0-9a-z]+ .*
#...
