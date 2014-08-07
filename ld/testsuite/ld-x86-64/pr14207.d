#name: PR ld/14207
#as: --64
#ld: -mcgc_x86_64 -shared -z relro -z now
#readcgc: -l --wide

#failif
#...
  NULL +.*
#...
