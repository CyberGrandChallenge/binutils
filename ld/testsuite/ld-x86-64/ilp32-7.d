#as: --x32
#ld: -m cgc32_x86_64 -Ttext-segment 0xe0000000
#error: .*relocation truncated to fit: R_X86_64_32S.*
