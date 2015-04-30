OUTPUT_FORMAT("cgc32-m68k", "cgc32-m68k",
              "cgc32-m68k")
OUTPUT_ARCH(m68k)
ENTRY(_start)

SECTIONS {
 
  .text : {_start = .; *(.text)}
}
