#source: ifunc-19b.s
#source: ifunc-19a.s
#as: --64
#ld: -shared -mcgc_x86_64 -z nocombreloc
#readcgc: -r --wide
#target: x86_64-*-*

Relocation section '.rela.ifunc' at .*
[ ]+Offset[ ]+Info[ ]+Type[ ]+.*
[0-9a-f]+[ ]+[0-9a-f]+[ ]+R_X86_64_IRELATIVE[ ]+[0-9a-f]*

Relocation section '.rela.plt' at .*
[ ]+Offset[ ]+Info[ ]+Type[ ]+.*
[0-9a-f]+[ ]+[0-9a-f]+[ ]+R_X86_64_IRELATIVE[ ]+[0-9a-f]*
