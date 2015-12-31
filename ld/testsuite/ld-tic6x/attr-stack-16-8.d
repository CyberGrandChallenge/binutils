#name: C6X stack attribute merging, 16 8
#as: -mlittle-endian
#ld: -r -mcgc32_tic6x_le
#source: attr-stack-16.s
#source: attr-stack-8.s
#error: .*requires more stack alignment than .* preserves
