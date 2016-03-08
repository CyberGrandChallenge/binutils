#source: pr349-1.s
#source: pr349-2.s
#ld: -r
#readcgc: -S
#xfail: arc-*-* d30v-*-* dlx-*-* fr30-*-* frv-*-cgc i860-*-* i960-*-*
#xfail: iq*-*-* mn10200-*-* moxie-*-* msp*-*-* mt-*-* or32-*-* pj*-*-*
# if not using cgc32.em, you don't get fancy section handling

#...
.* .abcxyz .*
#...
.* .abcxyz .*
#pass
