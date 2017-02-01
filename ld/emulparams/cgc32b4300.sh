# If you change this file, please also look at files which source this one:
# cgc32l4300.sh

EMBEDDED=yes
. ${srcdir}/emulparams/cgc32bmip.sh
TEXT_START_ADDR=0xa0020000
unset SHLIB_TEXT_START_ADDR
EXECUTABLE_SYMBOLS='_DYNAMIC_LINK = 0;'
DYNAMIC_LINK=FALSE
