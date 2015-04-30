#name: PR ld/14215
#as: --32
#ld: -mcgc_i386 -shared -z relro
#readcgc: -l --wide

#failif
#...
   03     .dynamic .got .data 
#...
