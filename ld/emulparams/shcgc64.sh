# Note: this is sourced in turn by shlcgc64.sh
OUTPUT_FORMAT=${OUTPUT_FORMAT-"cgc64-sh64"}
CGCSIZE=64

EXTRA_EM_FILE=
. ${srcdir}/emulparams/shcgc32.sh

# We do not need .cranges
test -z "$CREATE_SHLIB" && OTHER_SECTIONS="
 .stack ${RELOCATING-0}${RELOCATING+(DEFINED(_stack) ? _stack : ALIGN (0x40000) + 0x80000)} :
  {
    ${RELOCATING+_stack = .;}
    *(.stack)
    LONG(0xdeaddead)
  }
"
# We do not need .stack for shared library.
test -n "$CREATE_SHLIB" && OTHER_SECTIONS=""
