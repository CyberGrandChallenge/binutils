. ${srcdir}/emulparams/cgc64bmip-defs.sh
OUTPUT_FORMAT="cgc64-bigmips"
BIG_OUTPUT_FORMAT="cgc64-bigmips"
LITTLE_OUTPUT_FORMAT="cgc64-littlemips"
SHLIB_TEXT_START_ADDR=0x3ffffe0000

# IRIX6 defines these symbols.  0x40 is the size of the CGC header.
EXECUTABLE_SYMBOLS="
  __dso_displacement = 0;
  ${CREATE_SHLIB-${CREATE_PIE-__cgc_header = ${TEXT_START_ADDR};}}
  ${CREATE_SHLIB+__cgc_header = ${SHLIB_TEXT_START_ADDR};}
  ${CREATE_PIE+__cgc_header = ${SHLIB_TEXT_START_ADDR};}
  __program_header_table = __cgc_header + 0x40;
"

# There are often dynamic relocations against the .rodata section.
# Setting DT_TEXTREL in the .dynamic section does not convince the
# IRIX6 linker to permit relocations against the text segment.
# Following the IRIX linker, we simply put .rodata in the data
# segment.
WRITABLE_RODATA=

EXTRA_EM_FILE=irix
