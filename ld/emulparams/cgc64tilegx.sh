SCRIPT_NAME=cgc
OUTPUT_FORMAT="cgc64-tilegx-le"
BIG_OUTPUT_FORMAT="cgc64-tilegx-be"
LITTLE_OUTPUT_FORMAT="cgc64-tilegx-le"
TEXT_START_ADDR=0x10000
NO_REL_RELOCS=yes
MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"
COMMONPAGESIZE="CONSTANT (COMMONPAGESIZE)"
# See also `include/cgc/tilegx.h'
ARCH=tilegx
ALIGNMENT=64
MACHINE=
NOP=0
# Note that "cgc32.em" actually handles cgc64 also.
TEMPLATE_NAME=cgc32
GENERATE_SHLIB_SCRIPT=yes
GENERATE_COMBRELOC_SCRIPT=yes
GENERATE_PIE_SCRIPT=yes
NO_SMALL_DATA=yes
SEPARATE_GOTPLT="SIZEOF (.got.plt) >= 16 ? 16 : 0"
OTHER_SECTIONS="
  /* TILE architecture interrupt vector areas */
  .intrpt0 0xfffffffffc000000 : { KEEP(*(.intrpt0)) }
  .intrpt1 0xfffffffffd000000 : { KEEP(*(.intrpt1)) }
  .intrpt2 0xfffffffffe000000 : { KEEP(*(.intrpt2)) }
  .intrpt3 0xffffffffff000000 : { KEEP(*(.intrpt3)) }
"
