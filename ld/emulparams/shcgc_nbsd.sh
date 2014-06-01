# If you change this file, please alsolook at files which source this one:
# shlcgc_nbsd.sh

. ${srcdir}/emulparams/shcgc.sh

OUTPUT_FORMAT="cgc32-sh-nbsd"
TEXT_START_ADDR=0x400000
MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"

DATA_START_SYMBOLS='PROVIDE (__data_start = .);';

ENTRY=_start

unset EMBEDDED
unset OTHER_SECTIONS
