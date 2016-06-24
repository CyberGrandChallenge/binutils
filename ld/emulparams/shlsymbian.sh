TEXT_START_ADDR=0x8000
SHLIB_TEXT_START_ADDR=0x8000
SHLIB_DATA_ADDR=0x400000

. ${srcdir}/emulparams/shcgc.sh

# Use only two underscores for the constructor/destructor symbols
CTOR_START='__ctors = .;'
CTOR_END='__ctors_end = .;'
DTOR_START='__dtors = .;'
DTOR_END='__dtors_end = .;'

# Suppress the .stack section.
test -z "$CREATE_SHLIB" && OTHER_SECTIONS="${RELOCATING+PROVIDE (_stack = 0x30000);}"

OUTPUT_FORMAT="cgc32-shl-symbian"
SCRIPT_NAME=cgc32sh-symbian
