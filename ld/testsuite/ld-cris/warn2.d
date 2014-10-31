#source: start1.s
#source: globsym1ref.s
#source: globsymw1.s
#target: cris-*-*cgc* cris-*-*aout*
#as: --em=criself
#ld: -mcriself
#objdump: -p
# There should be no warning, since the symbol warned about is
# missing from the construct.
.*:     file format cgc32.*-cris
#pass
