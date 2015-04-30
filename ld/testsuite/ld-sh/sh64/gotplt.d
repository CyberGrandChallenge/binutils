#source: gotplt.s
#as: --abi=32 --isa=SHmedia
#ld: -shared -mshcgc32 --version-script=$srcdir/$subdir/gotplt.map
#readcgc: -r
#target: sh64-*-cgc

# Make sure that gotplt relocations of forced local symbols
# use the GOT.

Relocation section '\.rela\.dyn' at offset .* contains 1 entries:
 Offset     Info    Type            Sym\.Value  Sym\. Name \+ Addend
[0-9a-f ]+R_SH_RELATIVE[0-9a-f ]+
