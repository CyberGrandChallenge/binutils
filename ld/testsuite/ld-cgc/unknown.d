#source: ../../../binutils/testsuite/binutils-all/unknown.s
#ld: -r
#readcgc: -S

#...
  \[[ 0-9]+\] \.foo[ \t]+NOTE[ \t]+.*
#pass
