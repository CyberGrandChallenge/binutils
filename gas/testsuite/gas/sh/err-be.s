! { dg-do assemble { target sh*-*-cgc} }
! { dg-options "-little" }
! { dg-error "-big required" "" { target sh*-*-cgc } 0 }

! Check that a mismatch between command-line options and the .big
! directive is identified.

	.big
start:
	nop
