#objdump: -p
#as:	  -m68hc11 -mshort-double
#name:	  Cgc flags 68HC11 16-bit int, 32-bit double
#source:  abi.s

.*: +file format cgc32\-m68hc11
private flags = 0:\[abi=16-bit int, 32-bit double, cpu=HC11\] \[memory=flat\]
