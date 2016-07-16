#name: C6X compatibility attribute merging, gnu other
#as: -mlittle-endian
#ld: -r -mcgc32_tic6x_le
#source: attr-compatibility-gnu.s
#source: attr-compatibility-other.s
#error: .*Object has vendor-specific contents that must be processed by the 'other' toolchain
