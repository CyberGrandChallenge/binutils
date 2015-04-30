# If you change this file, please also look at files which source this one:
# cgc32ltsmipn32.sh

. ${srcdir}/emulparams/cgc32bmipn32-defs.sh
OUTPUT_FORMAT="cgc32-ntradbigmips"
BIG_OUTPUT_FORMAT="cgc32-ntradbigmips"
LITTLE_OUTPUT_FORMAT="cgc32-ntradlittlemips"
COMMONPAGESIZE="CONSTANT (COMMONPAGESIZE)"

# Magic sections.
OTHER_TEXT_SECTIONS='*(.mips16.fn.*) *(.mips16.call.*)'
OTHER_SECTIONS='
  .gptab.sdata : { *(.gptab.data) *(.gptab.sdata) }
  .gptab.sbss : { *(.gptab.bss) *(.gptab.sbss) }
'
