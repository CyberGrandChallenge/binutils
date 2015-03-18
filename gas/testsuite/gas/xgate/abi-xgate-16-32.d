#objdump: -p
#as:	  -mshort-double
#name:	  Cgc flags XGATE 16-bit int, 32-bit double
#source:  abi.s

.*: +file format cgc32\-xgate
private flags = 80:\[abi=16-bit int, 32-bit double, cpu=XGATE\]

