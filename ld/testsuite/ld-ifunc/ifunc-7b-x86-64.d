#source: ifunc-7-x86-64.s
#as: --64
#ld: -mcgc_x86_64 -shared
#readcgc: -r --wide
#target: x86_64-*-*

Relocation section '.rela.plt' at .*
[ ]+Offset[ ]+Info[ ]+Type[ ]+.*
[0-9a-f]+[ ]+[0-9a-f]+[ ]+R_X86_64_IRELATIVE[ ]+[0-9a-f]*
