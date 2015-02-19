/* Simple script for testing relaxation */

OUTPUT_FORMAT("cgc32-littlenios2", "cgc32-littlenios2", "cgc32-littlenios2")
OUTPUT_ARCH(nios2)
ENTRY(_start)
SECTIONS
{
	_start = .;
	text2 0 : { *(text2) }
	text1 0x8000 : { *(text1) }
}
