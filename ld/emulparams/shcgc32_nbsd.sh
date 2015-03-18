# If you change this file, please alsolook at files which source this one:
# shlcgc32_nbsd.sh

. ${srcdir}/emulparams/shcgc32.sh

OUTPUT_FORMAT="cgc32-sh64-nbsd"
TEXT_START_ADDR=0x400000
MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"

ENTRY=__start

unset EMBEDDED
unset STACK_ADDR
unset OTHER_SECTIONS
OTHER_SECTIONS="
  .cranges 0 : { *(.cranges) }
"
