#source: reloc-num16.s
#ld: -T $srcdir/$subdir/crx.ld
#objdump: -D

# Test relocation on data R_CRX_NUM16

.*:     file format cgc32-crx

Disassembly of section .text:

.* <_start>:
.*:	34 12       	addcw	\$0x3, r4
