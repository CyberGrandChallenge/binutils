#name: MIPS relax-jalr-shared n64
#source: relax-jalr.s
#as: -march=from-abi -KPIC -64 -EB
#objdump: --prefix-addresses -d --show-raw-insn
#ld: --relax -shared -mcgc64btsmip

.*:     file format cgc.*mips.*

Disassembly of section \.text:
	\.\.\.
	\.\.\.
.*	ld	t9,.*
.*	jalr	t9
.*	nop
	\.\.\.
.*	ld	t9,.*
.*	jalr	t9
.*	nop
	\.\.\.
.*	ld	t9,.*
.*	bal	.* <__start>
.*	nop
	\.\.\.
