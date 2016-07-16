#source: init.s
#as: --abi=32 --isa=SHmedia
#ld: -shared -mshcgc32
#readcgc: -d
#target: sh64-*-cgc

# Make sure that the lsb of DT_INIT and DT_FINI entries is set
# when _init and _fini are SHmedia code.

.*
  Tag        Type                         Name/Value
 0x0000000c \(INIT\) .*[13579bdf]
 0x0000000d \(FINI\) .*[13579bdf]
#pass
