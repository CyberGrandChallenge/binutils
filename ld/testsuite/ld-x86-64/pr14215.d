#name: PR ld/14215
#as: --64
#ld: -mcgc_x86_64 -shared -z relro
#readcgc: -l --wide

#failif
#...
   03     .dynamic .got .data 
#...
