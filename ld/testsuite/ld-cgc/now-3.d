#source: start.s
#readcgc: -d -W
#ld: -shared -z now
#target: *-*-linux* *-*-gnu*

#failif
#...
 0x[0-9a-f]+ +\(FLAGS\) +BIND_NOW
#pass
