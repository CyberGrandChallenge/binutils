#! /bin/sh

m4 -DCGC32 test1cgc.asm >test1cgc32.s
m4 -DCGC64 test1cgc.asm >test1cgc64.s
m4 -DXCOFF32 test1xcoff.asm >test1xcoff32.s
#m4 -DXCOFF64 test1xcoff.asm >test1xcoff64.s
