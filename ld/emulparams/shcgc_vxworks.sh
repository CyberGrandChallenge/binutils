# If you change this file, please also look at files which source this one:
# shlcgc_vxworks.sh

SCRIPT_NAME=cgc
NO_REL_RELOCS=yes
BIG_OUTPUT_FORMAT="cgc32-sh-vxworks"
LITTLE_OUTPUT_FORMAT="cgc32-shl-vxworks"
OUTPUT_FORMAT="$BIG_OUTPUT_FORMAT"
TEXT_START_ADDR=0x1000
MAXPAGESIZE='CONSTANT (MAXPAGESIZE)'
ARCH=sh
MACHINE=
TEMPLATE_NAME=cgc32
GENERATE_SHLIB_SCRIPT=yes
ENTRY=__start
SYMPREFIX=_
GOT=".got          ${RELOCATING-0} : {
  PROVIDE(__GLOBAL_OFFSET_TABLE_ = .);
  *(.got.plt) *(.got) }"
. ${srcdir}/emulparams/vxworks.sh
