#ld:
#target: cris-*-*cgc* cris-*-*aout*
#objdump: -p

# Check that we can link an object that doesn't have any global symbols;
# where cgc_sym_hashes(bfd) is NULL.

.*:     file format .*-cris
#pass
