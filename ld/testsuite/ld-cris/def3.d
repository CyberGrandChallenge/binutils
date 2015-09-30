#source: start1.s
#source: stabs1.s
#source: globsymw1.s
#target: cris-*-*cgc* cris-*-*aout*
#as: --em=criself
#ld: -mcriself
#objdump: -p
# Just checking that undef3 links correctly when given a symbol.
.*:     file format cgc32.*-cris
#pass
