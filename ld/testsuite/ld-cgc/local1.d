#ld: -shared --version-script local1.map
#readcgc: -s --wide
#target: *-*-linux* *-*-gnu*

#...
    .*: [0-9a-f]* +[0-9a-f]+ +OBJECT +LOCAL +DEFAULT +[0-9] +foo
#...
