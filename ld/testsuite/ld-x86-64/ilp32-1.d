#source: dummy.s
#as: --x32
#ld: -m cgc32_x86_64 tmpdir/startx32.o tmpdir/foox32.o
#readcgc: -h

CGC Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             CGC32
  Data:                              2's complement, little endian
  Version:                           1 \(current\)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC \(Executable file\)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
#pass
