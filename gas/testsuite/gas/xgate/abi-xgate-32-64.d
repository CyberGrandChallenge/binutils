#objdump: -p
#as:	  -mlong
#name:	  Cgc flags XGATE 32-bit int, 64-bit double
#source:  abi.s

.*: +file format cgc32\-xgate
private flags = 83:\[abi=32-bit int, 64-bit double, cpu=XGATE\]
