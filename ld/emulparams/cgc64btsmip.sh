# If you change this file, please also look at files which source this one:
# cgc64ltsmip.sh

. ${srcdir}/emulparams/cgc64bmip-defs.sh
OUTPUT_FORMAT="cgc64-tradbigmips"
BIG_OUTPUT_FORMAT="cgc64-tradbigmips"
LITTLE_OUTPUT_FORMAT="cgc64-tradlittlemips"

# Magic sections.
OTHER_TEXT_SECTIONS='*(.mips16.fn.*) *(.mips16.call.*)'
OTHER_SECTIONS='
  .gptab.sdata : { *(.gptab.data) *(.gptab.sdata) }
  .gptab.sbss : { *(.gptab.bss) *(.gptab.sbss) }
'

TEXT_START_ADDR="0x120000000"
