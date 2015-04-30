! { dg-do assemble { target sh*-*-cgc} }
! { dg-options "-big" }
! { dg-error "-little required" "" { target sh*-*-cgc } 0 }

! Check that a mismatch between command-line options and the .big
! directive is identified.

	.little
start:
	nop
