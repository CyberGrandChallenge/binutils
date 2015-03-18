#source: ../../../cgc/group0.s
#readcgc: -SW
#name: group section

#...
[ 	]*\[.*\][ 	]+\.group[ 	]+GROUP.*
#...
[ 	]*\[.*\][ 	]+\.foo[ 	]+PROGBITS.*[ 	]+AXG[ 	]+.*
[ 	]*\[.*\][ 	]+\.bar[ 	]+PROGBITS.*[ 	]+AG[ 	]+.*
#pass
