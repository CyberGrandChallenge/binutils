#source: loc1.s
#source: start.s
#source: loc2.s
#ld: -m cgc64mmix
#objdump: -str
#error: multiple definition of `__\.MMIX\.start\.\.text'
