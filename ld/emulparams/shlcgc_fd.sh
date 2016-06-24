# If you change this file, please also look at files which source this one:
# shcgc_fd.sh

. ${srcdir}/emulparams/shlcgc_linux.sh
OUTPUT_FORMAT="cgc32-sh-fdpic"
GOT=".got          ${RELOCATING-0} : { *(.got.funcdesc) *(.got.plt) *(.got) }"
OTHER_GOT_RELOC_SECTIONS="
  .rela.got.funcdesc      ${RELOCATING-0} : { *(.rela.got.funcdesc) }
"
OTHER_READONLY_SECTIONS="
  .rofixup        : {
    ${RELOCATING+__ROFIXUP_LIST__ = .;}
    *(.rofixup)
    ${RELOCATING+__ROFIXUP_END__ = .;}
  }
"
