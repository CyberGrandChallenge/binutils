	.text
	.globl	_start
	.globl	__start
_start:
__start:
	.ifdef	HPUX
foo	.comm	4
	.else
	.comm	foo, 4, 4
	.endif
	.section .debug_foo,"",%progbits
	.balign	16
	.ifdef	CGC64
	.8byte	foo
	.else
	.4byte	foo
	.endif
	.balign	16
