#objdump: -r
#name: alpha cgc-reloc-1

.*:     file format cgc64-alpha.*

RELOCATION RECORDS FOR \[\.text\]:
OFFSET           TYPE              VALUE 
0*0000004 CGC_LITERAL       a
0*0000000 LITUSE            \.text\+0x0*0000002
0*000000c LITUSE            \.text\+0x0*0000001
0*0000008 CGC_LITERAL       b
0*0000010 CGC_LITERAL       f
0*0000014 LITUSE            \.text\+0x0*0000003
0*0000014 HINT              f
0*0000018 GPREL16           c
0*000001c GPRELHIGH         d
0*0000020 GPRELLOW          e
0*0000024 GPDISP            \.text\+0x0*0000008
0*0000030 GPDISP            \.text-0x0*0000008


