#source: dummy.s
#as: --32
#ld: -m cgc_i386 tmpdir/start32.o tmpdir/foo32.o
#readcgc: -h

CGC Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             CGC32
  Data:                              2's complement, little endian
  Version:                           1 \(current\)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC \(Executable file\)
  Machine:                           Intel 80386
  Version:                           0x1
#pass
