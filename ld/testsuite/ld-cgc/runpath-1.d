#source: start.s
#readcgc: -d -W
#ld: -shared -rpath . --enable-new-dtags
#target: *-*-linux* *-*-gnu*

#failif
#...
 +0x[0-9a-f]+ +\(RPATH\) +Library rpath: +\[.\]
#...
