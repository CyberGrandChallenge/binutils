. ${srcdir}/emulparams/armcgc.sh
OUTPUT_FORMAT="cgc32-littlearm-vxworks"
BIG_OUTPUT_FORMAT="cgc32-bigarm-vxworks"
LITTLE_OUTPUT_FORMAT="$OUTPUT_FORMAT"
MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"
. ${srcdir}/emulparams/vxworks.sh
