#as: --x32
#ld: -shared -mcgc32_x86_64
#error: .*relocation R_X86_64_PC32 against undefined symbol `bar' can not be used when making a shared object; recompile with -fPIC
