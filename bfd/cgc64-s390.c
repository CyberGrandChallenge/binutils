/* IBM S/390-specific support for 64-bit CGC
   Copyright 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
   2010, 2011, 2012 Free Software Foundation, Inc.
   Contributed Martin Schwidefsky (schwidefsky@de.ibm.com).

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#include "sysdep.h"
#include "bfd.h"
#include "bfdlink.h"
#include "libbfd.h"
#include "cgc-bfd.h"
#include "cgc/s390.h"

/* In case we're on a 32-bit machine, construct a 64-bit "-1" value
   from smaller values.  Start with zero, widen, *then* decrement.  */
#define MINUS_ONE      (((bfd_vma)0) - 1)

static bfd_reloc_status_type
s390_tls_reloc (bfd *, arelent *, asymbol *, void *,
		asection *, bfd *, char **);
static bfd_reloc_status_type
s390_cgc_ldisp_reloc (bfd *, arelent *, asymbol *, void *,
		      asection *, bfd *, char **);

/* The relocation "howto" table.  */
static reloc_howto_type cgc_howto_table[] =
{
  HOWTO (R_390_NONE,		/* type */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = 2 byte, 2 = 4 byte) */
	 0,			/* bitsize */
	 FALSE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 bfd_cgc_generic_reloc, /* special_function */
	 "R_390_NONE",		/* name */
	 FALSE,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 FALSE),		/* pcrel_offset */

  HOWTO(R_390_8,         0, 0,  8, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_8",        FALSE, 0,0x000000ff, FALSE),
  HOWTO(R_390_12,        0, 1, 12, FALSE, 0, complain_overflow_dont,
	bfd_cgc_generic_reloc, "R_390_12",       FALSE, 0,0x00000fff, FALSE),
  HOWTO(R_390_16,        0, 1, 16, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_16",       FALSE, 0,0x0000ffff, FALSE),
  HOWTO(R_390_32,        0, 2, 32, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_32",       FALSE, 0,0xffffffff, FALSE),
  HOWTO(R_390_PC32,	 0, 2, 32,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PC32",     FALSE, 0,0xffffffff, TRUE),
  HOWTO(R_390_GOT12,	 0, 1, 12, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOT12",    FALSE, 0,0x00000fff, FALSE),
  HOWTO(R_390_GOT32,	 0, 2, 32, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOT32",    FALSE, 0,0xffffffff, FALSE),
  HOWTO(R_390_PLT32,	 0, 2, 32,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLT32",    FALSE, 0,0xffffffff, TRUE),
  HOWTO(R_390_COPY,      0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_COPY",     FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_GLOB_DAT,  0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GLOB_DAT", FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_JMP_SLOT,  0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_JMP_SLOT", FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_RELATIVE,  0, 4, 64,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_RELATIVE", FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_GOTOFF32,  0, 2, 32, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTOFF32", FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_GOTPC,     0, 4, 64,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTPC",    FALSE, 0,MINUS_ONE,  TRUE),
  HOWTO(R_390_GOT16,     0, 1, 16, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOT16",    FALSE, 0,0x0000ffff, FALSE),
  HOWTO(R_390_PC16,      0, 1, 16,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PC16",     FALSE, 0,0x0000ffff, TRUE),
  HOWTO(R_390_PC16DBL,   1, 1, 16,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PC16DBL",  FALSE, 0,0x0000ffff, TRUE),
  HOWTO(R_390_PLT16DBL,  1, 1, 16,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLT16DBL", FALSE, 0,0x0000ffff, TRUE),
  HOWTO(R_390_PC32DBL,	 1, 2, 32,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PC32DBL",  FALSE, 0,0xffffffff, TRUE),
  HOWTO(R_390_PLT32DBL,	 1, 2, 32,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLT32DBL", FALSE, 0,0xffffffff, TRUE),
  HOWTO(R_390_GOTPCDBL,  1, 2, 32,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTPCDBL", FALSE, 0,MINUS_ONE,  TRUE),
  HOWTO(R_390_64,        0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_64",       FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_PC64,	 0, 4, 64,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PC64",     FALSE, 0,MINUS_ONE,  TRUE),
  HOWTO(R_390_GOT64,	 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOT64",    FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_PLT64,	 0, 4, 64,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLT64",    FALSE, 0,MINUS_ONE,  TRUE),
  HOWTO(R_390_GOTENT,	 1, 2, 32,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTENT",   FALSE, 0,MINUS_ONE,  TRUE),
  HOWTO(R_390_GOTOFF16,  0, 1, 16, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTOFF16", FALSE, 0,0x0000ffff, FALSE),
  HOWTO(R_390_GOTOFF64,  0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTOFF64", FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_GOTPLT12,	 0, 1, 12, FALSE, 0, complain_overflow_dont,
	bfd_cgc_generic_reloc, "R_390_GOTPLT12", FALSE, 0,0x00000fff, FALSE),
  HOWTO(R_390_GOTPLT16,  0, 1, 16, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTPLT16", FALSE, 0,0x0000ffff, FALSE),
  HOWTO(R_390_GOTPLT32,	 0, 2, 32, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTPLT32", FALSE, 0,0xffffffff, FALSE),
  HOWTO(R_390_GOTPLT64,	 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTPLT64", FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_GOTPLTENT, 1, 2, 32,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_GOTPLTENT",FALSE, 0,MINUS_ONE,  TRUE),
  HOWTO(R_390_PLTOFF16,  0, 1, 16, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLTOFF16", FALSE, 0,0x0000ffff, FALSE),
  HOWTO(R_390_PLTOFF32,  0, 2, 32, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLTOFF32", FALSE, 0,0xffffffff, FALSE),
  HOWTO(R_390_PLTOFF64,  0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLTOFF64", FALSE, 0,MINUS_ONE,  FALSE),
  HOWTO(R_390_TLS_LOAD, 0, 0, 0, FALSE, 0, complain_overflow_dont,
	s390_tls_reloc, "R_390_TLS_LOAD", FALSE, 0, 0, FALSE),
  HOWTO(R_390_TLS_GDCALL, 0, 0, 0, FALSE, 0, complain_overflow_dont,
	s390_tls_reloc, "R_390_TLS_GDCALL", FALSE, 0, 0, FALSE),
  HOWTO(R_390_TLS_LDCALL, 0, 0, 0, FALSE, 0, complain_overflow_dont,
	s390_tls_reloc, "R_390_TLS_LDCALL", FALSE, 0, 0, FALSE),
  EMPTY_HOWTO (R_390_TLS_GD32),	/* Empty entry for R_390_TLS_GD32.  */
  HOWTO(R_390_TLS_GD64,  0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_GD64", FALSE, 0, MINUS_ONE, FALSE),
  HOWTO(R_390_TLS_GOTIE12, 0, 1, 12, FALSE, 0, complain_overflow_dont,
	bfd_cgc_generic_reloc, "R_390_TLS_GOTIE12", FALSE, 0, 0x00000fff, FALSE),
  EMPTY_HOWTO (R_390_TLS_GOTIE32),	/* Empty entry for R_390_TLS_GOTIE32.  */
  HOWTO(R_390_TLS_GOTIE64, 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_GOTIE64", FALSE, 0, MINUS_ONE, FALSE),
  EMPTY_HOWTO (R_390_TLS_LDM32),	/* Empty entry for R_390_TLS_LDM32.  */
  HOWTO(R_390_TLS_LDM64, 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_LDM64", FALSE, 0, MINUS_ONE, FALSE),
  EMPTY_HOWTO (R_390_TLS_IE32),	/* Empty entry for R_390_TLS_IE32.  */
  HOWTO(R_390_TLS_IE64,  0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_IE64", FALSE, 0, MINUS_ONE, FALSE),
  HOWTO(R_390_TLS_IEENT, 1, 2, 32, TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_IEENT", FALSE, 0, MINUS_ONE, TRUE),
  EMPTY_HOWTO (R_390_TLS_LE32),	/* Empty entry for R_390_TLS_LE32.  */
  HOWTO(R_390_TLS_LE64,  0, 2, 32, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_LE64", FALSE, 0, MINUS_ONE, FALSE),
  EMPTY_HOWTO (R_390_TLS_LDO32),	/* Empty entry for R_390_TLS_LDO32.  */
  HOWTO(R_390_TLS_LDO64, 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_LDO64", FALSE, 0, MINUS_ONE, FALSE),
  HOWTO(R_390_TLS_DTPMOD, 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_DTPMOD", FALSE, 0, MINUS_ONE, FALSE),
  HOWTO(R_390_TLS_DTPOFF, 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_DTPOFF", FALSE, 0, MINUS_ONE, FALSE),
  HOWTO(R_390_TLS_TPOFF, 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_TLS_TPOFF", FALSE, 0, MINUS_ONE, FALSE),
  HOWTO(R_390_20,        0, 2, 20, FALSE, 8, complain_overflow_dont,
	s390_cgc_ldisp_reloc, "R_390_20",      FALSE, 0,0x0fffff00, FALSE),
  HOWTO(R_390_GOT20,	 0, 2, 20, FALSE, 8, complain_overflow_dont,
	s390_cgc_ldisp_reloc, "R_390_GOT20",   FALSE, 0,0x0fffff00, FALSE),
  HOWTO(R_390_GOTPLT20,  0, 2, 20, FALSE, 8, complain_overflow_dont,
	s390_cgc_ldisp_reloc, "R_390_GOTPLT20", FALSE, 0,0x0fffff00, FALSE),
  HOWTO(R_390_TLS_GOTIE20, 0, 2, 20, FALSE, 8, complain_overflow_dont,
	s390_cgc_ldisp_reloc, "R_390_TLS_GOTIE20", FALSE, 0,0x0fffff00, FALSE),
  HOWTO(R_390_IRELATIVE, 0, 4, 64, FALSE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_IRELATIVE", FALSE, 0, MINUS_ONE, FALSE),
  HOWTO(R_390_PC12DBL,   1, 1, 12,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PC12DBL",  FALSE, 0,0x00000fff, TRUE),
  HOWTO(R_390_PLT12DBL,  1, 1, 12,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLT12DBL", FALSE, 0,0x00000fff, TRUE),
  HOWTO(R_390_PC24DBL,   1, 2, 24,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PC24DBL",  FALSE, 0,0x00ffffff, TRUE),
  HOWTO(R_390_PLT24DBL,  1, 2, 24,  TRUE, 0, complain_overflow_bitfield,
	bfd_cgc_generic_reloc, "R_390_PLT24DBL", FALSE, 0,0x00ffffff, TRUE),
};

/* GNU extension to record C++ vtable hierarchy.  */
static reloc_howto_type cgc64_s390_vtinherit_howto =
  HOWTO (R_390_GNU_VTINHERIT, 0,4,0,FALSE,0,complain_overflow_dont, NULL, "R_390_GNU_VTINHERIT", FALSE,0, 0, FALSE);
static reloc_howto_type cgc64_s390_vtentry_howto =
  HOWTO (R_390_GNU_VTENTRY, 0,4,0,FALSE,0,complain_overflow_dont, _bfd_cgc_rel_vtable_reloc_fn,"R_390_GNU_VTENTRY", FALSE,0,0, FALSE);

static reloc_howto_type *
cgc_s390_reloc_type_lookup (bfd *abfd ATTRIBUTE_UNUSED,
			    bfd_reloc_code_real_type code)
{
  switch (code)
    {
    case BFD_RELOC_NONE:
      return &cgc_howto_table[(int) R_390_NONE];
    case BFD_RELOC_8:
      return &cgc_howto_table[(int) R_390_8];
    case BFD_RELOC_390_12:
      return &cgc_howto_table[(int) R_390_12];
    case BFD_RELOC_16:
      return &cgc_howto_table[(int) R_390_16];
    case BFD_RELOC_32:
      return &cgc_howto_table[(int) R_390_32];
    case BFD_RELOC_CTOR:
      return &cgc_howto_table[(int) R_390_32];
    case BFD_RELOC_32_PCREL:
      return &cgc_howto_table[(int) R_390_PC32];
    case BFD_RELOC_390_GOT12:
      return &cgc_howto_table[(int) R_390_GOT12];
    case BFD_RELOC_32_GOT_PCREL:
      return &cgc_howto_table[(int) R_390_GOT32];
    case BFD_RELOC_390_PLT32:
      return &cgc_howto_table[(int) R_390_PLT32];
    case BFD_RELOC_390_COPY:
      return &cgc_howto_table[(int) R_390_COPY];
    case BFD_RELOC_390_GLOB_DAT:
      return &cgc_howto_table[(int) R_390_GLOB_DAT];
    case BFD_RELOC_390_JMP_SLOT:
      return &cgc_howto_table[(int) R_390_JMP_SLOT];
    case BFD_RELOC_390_RELATIVE:
      return &cgc_howto_table[(int) R_390_RELATIVE];
    case BFD_RELOC_32_GOTOFF:
      return &cgc_howto_table[(int) R_390_GOTOFF32];
    case BFD_RELOC_390_GOTPC:
      return &cgc_howto_table[(int) R_390_GOTPC];
    case BFD_RELOC_390_GOT16:
      return &cgc_howto_table[(int) R_390_GOT16];
    case BFD_RELOC_16_PCREL:
      return &cgc_howto_table[(int) R_390_PC16];
    case BFD_RELOC_390_PC12DBL:
      return &cgc_howto_table[(int) R_390_PC12DBL];
    case BFD_RELOC_390_PLT12DBL:
      return &cgc_howto_table[(int) R_390_PLT12DBL];
    case BFD_RELOC_390_PC16DBL:
      return &cgc_howto_table[(int) R_390_PC16DBL];
    case BFD_RELOC_390_PLT16DBL:
      return &cgc_howto_table[(int) R_390_PLT16DBL];
    case BFD_RELOC_390_PC24DBL:
      return &cgc_howto_table[(int) R_390_PC24DBL];
    case BFD_RELOC_390_PLT24DBL:
      return &cgc_howto_table[(int) R_390_PLT24DBL];
    case BFD_RELOC_390_PC32DBL:
      return &cgc_howto_table[(int) R_390_PC32DBL];
    case BFD_RELOC_390_PLT32DBL:
      return &cgc_howto_table[(int) R_390_PLT32DBL];
    case BFD_RELOC_390_GOTPCDBL:
      return &cgc_howto_table[(int) R_390_GOTPCDBL];
    case BFD_RELOC_64:
      return &cgc_howto_table[(int) R_390_64];
    case BFD_RELOC_64_PCREL:
      return &cgc_howto_table[(int) R_390_PC64];
    case BFD_RELOC_390_GOT64:
      return &cgc_howto_table[(int) R_390_GOT64];
    case BFD_RELOC_390_PLT64:
      return &cgc_howto_table[(int) R_390_PLT64];
    case BFD_RELOC_390_GOTENT:
      return &cgc_howto_table[(int) R_390_GOTENT];
    case BFD_RELOC_16_GOTOFF:
      return &cgc_howto_table[(int) R_390_GOTOFF16];
    case BFD_RELOC_390_GOTOFF64:
      return &cgc_howto_table[(int) R_390_GOTOFF64];
    case BFD_RELOC_390_GOTPLT12:
      return &cgc_howto_table[(int) R_390_GOTPLT12];
    case BFD_RELOC_390_GOTPLT16:
      return &cgc_howto_table[(int) R_390_GOTPLT16];
    case BFD_RELOC_390_GOTPLT32:
      return &cgc_howto_table[(int) R_390_GOTPLT32];
    case BFD_RELOC_390_GOTPLT64:
      return &cgc_howto_table[(int) R_390_GOTPLT64];
    case BFD_RELOC_390_GOTPLTENT:
      return &cgc_howto_table[(int) R_390_GOTPLTENT];
    case BFD_RELOC_390_PLTOFF16:
      return &cgc_howto_table[(int) R_390_PLTOFF16];
    case BFD_RELOC_390_PLTOFF32:
      return &cgc_howto_table[(int) R_390_PLTOFF32];
    case BFD_RELOC_390_PLTOFF64:
      return &cgc_howto_table[(int) R_390_PLTOFF64];
    case BFD_RELOC_390_TLS_LOAD:
      return &cgc_howto_table[(int) R_390_TLS_LOAD];
    case BFD_RELOC_390_TLS_GDCALL:
      return &cgc_howto_table[(int) R_390_TLS_GDCALL];
    case BFD_RELOC_390_TLS_LDCALL:
      return &cgc_howto_table[(int) R_390_TLS_LDCALL];
    case BFD_RELOC_390_TLS_GD64:
      return &cgc_howto_table[(int) R_390_TLS_GD64];
    case BFD_RELOC_390_TLS_GOTIE12:
      return &cgc_howto_table[(int) R_390_TLS_GOTIE12];
    case BFD_RELOC_390_TLS_GOTIE64:
      return &cgc_howto_table[(int) R_390_TLS_GOTIE64];
    case BFD_RELOC_390_TLS_LDM64:
      return &cgc_howto_table[(int) R_390_TLS_LDM64];
    case BFD_RELOC_390_TLS_IE64:
      return &cgc_howto_table[(int) R_390_TLS_IE64];
    case BFD_RELOC_390_TLS_IEENT:
      return &cgc_howto_table[(int) R_390_TLS_IEENT];
    case BFD_RELOC_390_TLS_LE64:
      return &cgc_howto_table[(int) R_390_TLS_LE64];
    case BFD_RELOC_390_TLS_LDO64:
      return &cgc_howto_table[(int) R_390_TLS_LDO64];
    case BFD_RELOC_390_TLS_DTPMOD:
      return &cgc_howto_table[(int) R_390_TLS_DTPMOD];
    case BFD_RELOC_390_TLS_DTPOFF:
      return &cgc_howto_table[(int) R_390_TLS_DTPOFF];
    case BFD_RELOC_390_TLS_TPOFF:
      return &cgc_howto_table[(int) R_390_TLS_TPOFF];
    case BFD_RELOC_390_20:
      return &cgc_howto_table[(int) R_390_20];
    case BFD_RELOC_390_GOT20:
      return &cgc_howto_table[(int) R_390_GOT20];
    case BFD_RELOC_390_GOTPLT20:
      return &cgc_howto_table[(int) R_390_GOTPLT20];
    case BFD_RELOC_390_TLS_GOTIE20:
      return &cgc_howto_table[(int) R_390_TLS_GOTIE20];
    case BFD_RELOC_390_IRELATIVE:
      return &cgc_howto_table[(int) R_390_IRELATIVE];
    case BFD_RELOC_VTABLE_INHERIT:
      return &cgc64_s390_vtinherit_howto;
    case BFD_RELOC_VTABLE_ENTRY:
      return &cgc64_s390_vtentry_howto;
    default:
      break;
    }
  return 0;
}

static reloc_howto_type *
cgc_s390_reloc_name_lookup (bfd *abfd ATTRIBUTE_UNUSED,
			    const char *r_name)
{
  unsigned int i;

  for (i = 0;
       i < sizeof (cgc_howto_table) / sizeof (cgc_howto_table[0]);
       i++)
    if (cgc_howto_table[i].name != NULL
	&& strcasecmp (cgc_howto_table[i].name, r_name) == 0)
      return &cgc_howto_table[i];

    if (strcasecmp (cgc64_s390_vtinherit_howto.name, r_name) == 0)
      return &cgc64_s390_vtinherit_howto;
    if (strcasecmp (cgc64_s390_vtentry_howto.name, r_name) == 0)
      return &cgc64_s390_vtentry_howto;

  return NULL;
}

/* We need to use CGC64_R_TYPE so we have our own copy of this function,
   and cgc64-s390.c has its own copy.  */

static void
cgc_s390_info_to_howto (bfd *abfd ATTRIBUTE_UNUSED,
			arelent *cache_ptr,
			Cgc_Internal_Rela *dst)
{
  unsigned int r_type = CGC64_R_TYPE(dst->r_info);
  switch (r_type)
    {
    case R_390_GNU_VTINHERIT:
      cache_ptr->howto = &cgc64_s390_vtinherit_howto;
      break;

    case R_390_GNU_VTENTRY:
      cache_ptr->howto = &cgc64_s390_vtentry_howto;
      break;

    default:
      if (r_type >= sizeof (cgc_howto_table) / sizeof (cgc_howto_table[0]))
	{
	  (*_bfd_error_handler) (_("%B: invalid relocation type %d"),
				 abfd, (int) r_type);
	  r_type = R_390_NONE;
	}
      cache_ptr->howto = &cgc_howto_table[r_type];
    }
}

/* A relocation function which doesn't do anything.  */
static bfd_reloc_status_type
s390_tls_reloc (bfd *abfd ATTRIBUTE_UNUSED,
		arelent *reloc_entry,
		asymbol *symbol ATTRIBUTE_UNUSED,
		void * data ATTRIBUTE_UNUSED,
		asection *input_section,
		bfd *output_bfd,
		char **error_message ATTRIBUTE_UNUSED)
{
  if (output_bfd)
    reloc_entry->address += input_section->output_offset;
  return bfd_reloc_ok;
}

/* Handle the large displacement relocs.  */
static bfd_reloc_status_type
s390_cgc_ldisp_reloc (bfd *abfd,
		      arelent *reloc_entry,
		      asymbol *symbol,
		      void * data,
		      asection *input_section,
		      bfd *output_bfd,
		      char **error_message ATTRIBUTE_UNUSED)
{
  reloc_howto_type *howto = reloc_entry->howto;
  bfd_vma relocation;
  bfd_vma insn;

  if (output_bfd != (bfd *) NULL
      && (symbol->flags & BSF_SECTION_SYM) == 0
      && (! howto->partial_inplace
	  || reloc_entry->addend == 0))
    {
      reloc_entry->address += input_section->output_offset;
      return bfd_reloc_ok;
    }
  if (output_bfd != NULL)
    return bfd_reloc_continue;

  if (reloc_entry->address > bfd_get_section_limit (abfd, input_section))
    return bfd_reloc_outofrange;

  relocation = (symbol->value
		+ symbol->section->output_section->vma
		+ symbol->section->output_offset);
  relocation += reloc_entry->addend;
  if (howto->pc_relative)
    {
      relocation -= (input_section->output_section->vma
		     + input_section->output_offset);
      relocation -= reloc_entry->address;
    }

  insn = bfd_get_32 (abfd, (bfd_byte *) data + reloc_entry->address);
  insn |= (relocation & 0xfff) << 16 | (relocation & 0xff000) >> 4;
  bfd_put_32 (abfd, insn, (bfd_byte *) data + reloc_entry->address);

  if ((bfd_signed_vma) relocation < - 0x80000
      || (bfd_signed_vma) relocation > 0x7ffff)
    return bfd_reloc_overflow;
  else
    return bfd_reloc_ok;
}

static bfd_boolean
cgc_s390_is_local_label_name (bfd *abfd, const char *name)
{
  if (name[0] == '.' && (name[1] == 'X' || name[1] == 'L'))
    return TRUE;

  return _bfd_cgc_is_local_label_name (abfd, name);
}

/* Functions for the 390 CGC linker.  */

/* The name of the dynamic interpreter.  This is put in the .interp
   section.  */

#define CGC_DYNAMIC_INTERPRETER "/lib/ld64.so.1"

/* If ELIMINATE_COPY_RELOCS is non-zero, the linker will try to avoid
   copying dynamic variables from a shared lib into an app's dynbss
   section, and instead use a dynamic relocation to point into the
   shared lib.  */
#define ELIMINATE_COPY_RELOCS 1

/* The size in bytes of the first entry in the procedure linkage table.  */
#define PLT_FIRST_ENTRY_SIZE 32
/* The size in bytes of an entry in the procedure linkage table.  */
#define PLT_ENTRY_SIZE 32

#define GOT_ENTRY_SIZE 8

#define RELA_ENTRY_SIZE sizeof (Cgc64_External_Rela)

/* The first three entries in a procedure linkage table are reserved,
   and the initial contents are unimportant (we zero them out).
   Subsequent entries look like this.  See the SVR4 ABI 386
   supplement to see how this works.  */

/* For the s390, simple addr offset can only be 0 - 4096.
   To use the full 16777216 TB address space, several instructions
   are needed to load an address in a register and execute
   a branch( or just saving the address)

   Furthermore, only r 0 and 1 are free to use!!!  */

/* The first 3 words in the GOT are then reserved.
   Word 0 is the address of the dynamic table.
   Word 1 is a pointer to a structure describing the object
   Word 2 is used to point to the loader entry address.

   The code for PLT entries looks like this:

   The GOT holds the address in the PLT to be executed.
   The loader then gets:
   24(15) =  Pointer to the structure describing the object.
   28(15) =  Offset in symbol table
   The loader  must  then find the module where the function is
   and insert the address in the GOT.

   PLT1: LARL 1,<fn>@GOTENT # 6 bytes  Load address of GOT entry in r1
         LG   1,0(1)      # 6 bytes  Load address from GOT in r1
         BCR  15,1        # 2 bytes  Jump to address
   RET1: BASR 1,0         # 2 bytes  Return from GOT 1st time
         LGF  1,12(1)     # 6 bytes  Load offset in symbl table in r1
         BRCL 15,-x       # 6 bytes  Jump to start of PLT
         .long ?          # 4 bytes  offset into .rela.plt

   Total = 32 bytes per PLT entry
   Fixup at offset 2: relative address to GOT entry
   Fixup at offset 22: relative branch to PLT0
   Fixup at offset 28: 32 bit offset into .rela.plt

   A 32 bit offset into the symbol table is enough. It allows for
   .rela.plt sections up to a size of 2 gigabyte.  A single dynamic
   object (the main program, any shared library) is limited to 4GB in
   size.  Having a .rela.plt of 2GB would already make the .plt
   section bigger than 8GB.  */

static const bfd_byte cgc_s390x_plt_entry[PLT_ENTRY_SIZE] =
  {
    0xc0, 0x10, 0x00, 0x00, 0x00, 0x00,     /* larl    %r1,.       */
    0xe3, 0x10, 0x10, 0x00, 0x00, 0x04,     /* lg      %r1,0(%r1)  */
    0x07, 0xf1,                             /* br      %r1         */
    0x0d, 0x10,                             /* basr    %r1,%r0     */
    0xe3, 0x10, 0x10, 0x0c, 0x00, 0x14,     /* lgf     %r1,12(%r1) */
    0xc0, 0xf4, 0x00, 0x00, 0x00, 0x00,     /* jg      first plt   */
    0x00, 0x00, 0x00, 0x00                  /* .long   0x00000000  */
  };

/* The first PLT entry pushes the offset into the symbol table
   from R1 onto the stack at 56(15) and the loader object info
   at 48(15), loads the loader address in R1 and jumps to it.  */

/* The first entry in the PLT:

  PLT0:
     STG  1,56(15)  # r1 contains the offset into the symbol table
     LARL 1,_GLOBAL_OFFSET_TABLE # load address of global offset table
     MVC  48(8,15),8(1) # move loader ino (object struct address) to stack
     LG   1,16(1)   # get entry address of loader
     BCR  15,1      # jump to loader

     Fixup at offset 8: relative address to start of GOT.  */

static const bfd_byte cgc_s390x_first_plt_entry[PLT_FIRST_ENTRY_SIZE] =
  {
    0xe3, 0x10, 0xf0, 0x38, 0x00, 0x24,     /* stg     %r1,56(%r15)      */
    0xc0, 0x10, 0x00, 0x00, 0x00, 0x00,     /* larl    %r1,.             */
    0xd2, 0x07, 0xf0, 0x30, 0x10, 0x08,     /* mvc     48(8,%r15),8(%r1) */
    0xe3, 0x10, 0x10, 0x10, 0x00, 0x04,     /* lg      %r1,16(%r1)       */
    0x07, 0xf1,                             /* br      %r1               */
    0x07, 0x00,                             /* nopr    %r0               */
    0x07, 0x00,                             /* nopr    %r0               */
    0x07, 0x00                              /* nopr    %r0               */
  };


/* s390 CGC linker hash entry.  */

struct cgc_s390_link_hash_entry
{
  struct cgc_link_hash_entry cgc;

  /* Track dynamic relocs copied for this symbol.  */
  struct cgc_dyn_relocs *dyn_relocs;

  /* Number of GOTPLT references for a function.  */
  bfd_signed_vma gotplt_refcount;

#define GOT_UNKNOWN	0
#define GOT_NORMAL	1
#define GOT_TLS_GD	2
#define GOT_TLS_IE	3
#define GOT_TLS_IE_NLT	3
  unsigned char tls_type;

  /* For pointer equality reasons we might need to change the symbol
     type from STT_GNU_IFUNC to STT_FUNC together with its value and
     section entry.  So after alloc_dynrelocs only these values should
     be used.  In order to check whether a symbol is IFUNC use
     s390_is_ifunc_symbol_p.  */
  bfd_vma ifunc_resolver_address;
  asection *ifunc_resolver_section;
};

#define cgc_s390_hash_entry(ent) \
  ((struct cgc_s390_link_hash_entry *)(ent))

/* This structure represents an entry in the local PLT list needed for
   local IFUNC symbols.  */
struct plt_entry
{
  /* The section of the local symbol.
     Set in relocate_section and used in finish_dynamic_sections.  */
  asection *sec;

  union
    {
      bfd_signed_vma refcount;
      bfd_vma offset;
    } plt;
};

/* NOTE: Keep this structure in sync with
   the one declared in cgc32-s390.c.  */
struct cgc_s390_obj_tdata
{
  struct cgc_obj_tdata root;

  /* A local PLT is needed for ifunc symbols.  */
  struct plt_entry *local_plt;

  /* TLS type for each local got entry.  */
  char *local_got_tls_type;
};

#define cgc_s390_tdata(abfd) \
  ((struct cgc_s390_obj_tdata *) (abfd)->tdata.any)

#define cgc_s390_local_plt(abfd) \
  (cgc_s390_tdata (abfd)->local_plt)

#define cgc_s390_local_got_tls_type(abfd) \
  (cgc_s390_tdata (abfd)->local_got_tls_type)

#define is_s390_cgc(bfd)				\
  (bfd_get_flavour (bfd) == bfd_target_cgc_flavour	\
   && cgc_tdata (bfd) != NULL				\
   && cgc_object_id (bfd) == S390_CGC_DATA)

static bfd_boolean
cgc_s390_mkobject (bfd *abfd)
{
  return bfd_cgc_allocate_object (abfd, sizeof (struct cgc_s390_obj_tdata),
				  S390_CGC_DATA);
}

static bfd_boolean
cgc_s390_object_p (bfd *abfd)
{
  /* Set the right machine number for an s390 cgc32 file.  */
  return bfd_default_set_arch_mach (abfd, bfd_arch_s390, bfd_mach_s390_64);
}

/* s390 CGC linker hash table.  */

struct cgc_s390_link_hash_table
{
  struct cgc_link_hash_table cgc;

  /* Short-cuts to get to dynamic linker sections.  */
  asection *sdynbss;
  asection *srelbss;
  asection *irelifunc;

  union {
    bfd_signed_vma refcount;
    bfd_vma offset;
  } tls_ldm_got;

  /* Small local sym cache.  */
  struct sym_cache sym_cache;
};

/* Get the s390 CGC linker hash table from a link_info structure.  */

#define cgc_s390_hash_table(p) \
  (cgc_hash_table_id ((struct cgc_link_hash_table *) ((p)->hash)) \
  == S390_CGC_DATA ? ((struct cgc_s390_link_hash_table *) ((p)->hash)) : NULL)

#define CGC64 1
#include "cgc-s390-common.c"

/* Create an entry in an s390 CGC linker hash table.  */

static struct bfd_hash_entry *
link_hash_newfunc (struct bfd_hash_entry *entry,
		   struct bfd_hash_table *table,
		   const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry = bfd_hash_allocate (table,
				 sizeof (struct cgc_s390_link_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = _bfd_cgc_link_hash_newfunc (entry, table, string);
  if (entry != NULL)
    {
      struct cgc_s390_link_hash_entry *eh;

      eh = (struct cgc_s390_link_hash_entry *) entry;
      eh->dyn_relocs = NULL;
      eh->gotplt_refcount = 0;
      eh->tls_type = GOT_UNKNOWN;
      eh->ifunc_resolver_address = 0;
      eh->ifunc_resolver_section = NULL;
    }

  return entry;
}

/* Create an s390 CGC linker hash table.  */

static struct bfd_link_hash_table *
cgc_s390_link_hash_table_create (bfd *abfd)
{
  struct cgc_s390_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct cgc_s390_link_hash_table);

  ret = (struct cgc_s390_link_hash_table *) bfd_zmalloc (amt);
  if (ret == NULL)
    return NULL;

  if (!_bfd_cgc_link_hash_table_init (&ret->cgc, abfd, link_hash_newfunc,
				      sizeof (struct cgc_s390_link_hash_entry),
				      S390_CGC_DATA))
    {
      free (ret);
      return NULL;
    }

  return &ret->cgc.root;
}

/* Create .got, .gotplt, and .rela.got sections in DYNOBJ, and set up
   shortcuts to them in our hash table.  */

static bfd_boolean
create_got_section (bfd *dynobj,
		    struct bfd_link_info *info)
{
  struct cgc_s390_link_hash_table *htab;

  if (! _bfd_cgc_create_got_section (dynobj, info))
    return FALSE;

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  htab->cgc.sgot = bfd_get_linker_section (dynobj, ".got");
  htab->cgc.sgotplt = bfd_get_linker_section (dynobj, ".got.plt");
  htab->cgc.srelgot = bfd_get_linker_section (dynobj, ".rela.got");
  if (!htab->cgc.sgot || !htab->cgc.sgotplt || !htab->cgc.srelgot)
    abort ();
  return TRUE;
}

/* Create .plt, .rela.plt, .got, .got.plt, .rela.got, .dynbss, and
   .rela.bss sections in DYNOBJ, and set up shortcuts to them in our
   hash table.  */

static bfd_boolean
cgc_s390_create_dynamic_sections (bfd *dynobj,
				  struct bfd_link_info *info)
{
  struct cgc_s390_link_hash_table *htab;

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  if (!htab->cgc.sgot && !create_got_section (dynobj, info))
    return FALSE;

  if (!_bfd_cgc_create_dynamic_sections (dynobj, info))
    return FALSE;

  htab->cgc.splt = bfd_get_linker_section (dynobj, ".plt");
  htab->cgc.srelplt = bfd_get_linker_section (dynobj, ".rela.plt");
  htab->sdynbss = bfd_get_linker_section (dynobj, ".dynbss");
  if (!info->shared)
    htab->srelbss = bfd_get_linker_section (dynobj, ".rela.bss");

  if (!htab->cgc.splt || !htab->cgc.srelplt || !htab->sdynbss
      || (!info->shared && !htab->srelbss))
    abort ();

  return TRUE;
}

/* Copy the extra info we tack onto an cgc_link_hash_entry.  */

static void
cgc_s390_copy_indirect_symbol (struct bfd_link_info *info,
			       struct cgc_link_hash_entry *dir,
			       struct cgc_link_hash_entry *ind)
{
  struct cgc_s390_link_hash_entry *edir, *eind;

  edir = (struct cgc_s390_link_hash_entry *) dir;
  eind = (struct cgc_s390_link_hash_entry *) ind;

  if (eind->dyn_relocs != NULL)
    {
      if (edir->dyn_relocs != NULL)
	{
	  struct cgc_dyn_relocs **pp;
	  struct cgc_dyn_relocs *p;

	  /* Add reloc counts against the indirect sym to the direct sym
	     list.  Merge any entries against the same section.  */
	  for (pp = &eind->dyn_relocs; (p = *pp) != NULL; )
	    {
	      struct cgc_dyn_relocs *q;

	      for (q = edir->dyn_relocs; q != NULL; q = q->next)
		if (q->sec == p->sec)
		  {
		    q->pc_count += p->pc_count;
		    q->count += p->count;
		    *pp = p->next;
		    break;
		  }
	      if (q == NULL)
		pp = &p->next;
	    }
	  *pp = edir->dyn_relocs;
	}

      edir->dyn_relocs = eind->dyn_relocs;
      eind->dyn_relocs = NULL;
    }

  if (ind->root.type == bfd_link_hash_indirect
      && dir->got.refcount <= 0)
    {
      edir->tls_type = eind->tls_type;
      eind->tls_type = GOT_UNKNOWN;
    }

  if (ELIMINATE_COPY_RELOCS
      && ind->root.type != bfd_link_hash_indirect
      && dir->dynamic_adjusted)
    {
      /* If called to transfer flags for a weakdef during processing
	 of cgc_adjust_dynamic_symbol, don't copy non_got_ref.
	 We clear it ourselves for ELIMINATE_COPY_RELOCS.  */
      dir->ref_dynamic |= ind->ref_dynamic;
      dir->ref_regular |= ind->ref_regular;
      dir->ref_regular_nonweak |= ind->ref_regular_nonweak;
      dir->needs_plt |= ind->needs_plt;
    }
  else
    _bfd_cgc_link_hash_copy_indirect (info, dir, ind);
}

static int
cgc_s390_tls_transition (struct bfd_link_info *info,
			 int r_type,
			 int is_local)
{
  if (info->shared)
    return r_type;

  switch (r_type)
    {
    case R_390_TLS_GD64:
    case R_390_TLS_IE64:
      if (is_local)
	return R_390_TLS_LE64;
      return R_390_TLS_IE64;
    case R_390_TLS_GOTIE64:
      if (is_local)
	return R_390_TLS_LE64;
      return R_390_TLS_GOTIE64;
    case R_390_TLS_LDM64:
      return R_390_TLS_LE64;
    }

  return r_type;
}

/* Look through the relocs for a section during the first phase, and
   allocate space in the global offset table or procedure linkage
   table.  */

static bfd_boolean
cgc_s390_check_relocs (bfd *abfd,
		       struct bfd_link_info *info,
		       asection *sec,
		       const Cgc_Internal_Rela *relocs)
{
  struct cgc_s390_link_hash_table *htab;
  Cgc_Internal_Shdr *symtab_hdr;
  struct cgc_link_hash_entry **sym_hashes;
  const Cgc_Internal_Rela *rel;
  const Cgc_Internal_Rela *rel_end;
  asection *sreloc;
  bfd_signed_vma *local_got_refcounts;
  int tls_type, old_tls_type;

  if (info->relocatable)
    return TRUE;

  BFD_ASSERT (is_s390_cgc (abfd));

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  symtab_hdr = &cgc_symtab_hdr (abfd);
  sym_hashes = cgc_sym_hashes (abfd);
  local_got_refcounts = cgc_local_got_refcounts (abfd);

  sreloc = NULL;

  rel_end = relocs + sec->reloc_count;
  for (rel = relocs; rel < rel_end; rel++)
    {
      unsigned int r_type;
      unsigned long r_symndx;
      struct cgc_link_hash_entry *h;
      Cgc_Internal_Sym *isym;

      r_symndx = CGC64_R_SYM (rel->r_info);

      if (r_symndx >= NUM_SHDR_ENTRIES (symtab_hdr))
	{
	  (*_bfd_error_handler) (_("%B: bad symbol index: %d"),
				 abfd,
				 r_symndx);
	  return FALSE;
	}

      if (r_symndx < symtab_hdr->sh_info)
	{
	  /* A local symbol.  */
	  isym = bfd_sym_from_r_symndx (&htab->sym_cache,
					abfd, r_symndx);
	  if (isym == NULL)
	    return FALSE;

	  if (CGC_ST_TYPE (isym->st_info) == STT_GNU_IFUNC)
	    {
	      struct plt_entry *plt;

	      if (htab->cgc.dynobj == NULL)
		htab->cgc.dynobj = abfd;

	      if (!s390_cgc_create_ifunc_sections (htab->cgc.dynobj, info))
		return FALSE;

	      if (local_got_refcounts == NULL)
		{
		  if (!cgc_s390_allocate_local_syminfo (abfd, symtab_hdr))
		    return FALSE;
		  local_got_refcounts = cgc_local_got_refcounts (abfd);
		}
	      plt = cgc_s390_local_plt (abfd);
	      plt[r_symndx].plt.refcount++;
	    }
	  h = NULL;
	}
      else
	{
	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct cgc_link_hash_entry *) h->root.u.i.link;

	  /* PR15323, ref flags aren't set for references in the same
	     object.  */
	  h->root.non_ir_ref = 1;
	}

      /* Create got section and local_got_refcounts array if they
	 are needed.  */
      r_type = cgc_s390_tls_transition (info,
					CGC64_R_TYPE (rel->r_info),
					h == NULL);
      switch (r_type)
	{
	case R_390_GOT12:
	case R_390_GOT16:
	case R_390_GOT20:
	case R_390_GOT32:
	case R_390_GOT64:
	case R_390_GOTENT:
	case R_390_GOTPLT12:
	case R_390_GOTPLT16:
	case R_390_GOTPLT20:
	case R_390_GOTPLT32:
	case R_390_GOTPLT64:
	case R_390_GOTPLTENT:
	case R_390_TLS_GD64:
	case R_390_TLS_GOTIE12:
	case R_390_TLS_GOTIE20:
	case R_390_TLS_GOTIE64:
	case R_390_TLS_IEENT:
	case R_390_TLS_IE64:
	case R_390_TLS_LDM64:
	  if (h == NULL
	      && local_got_refcounts == NULL)
	    {
	      if (!cgc_s390_allocate_local_syminfo (abfd, symtab_hdr))
		return FALSE;
	      local_got_refcounts = cgc_local_got_refcounts (abfd);
	    }

	  /* Fall through.  */
	case R_390_GOTOFF16:
	case R_390_GOTOFF32:
	case R_390_GOTOFF64:
	case R_390_GOTPC:
	case R_390_GOTPCDBL:
	  if (htab->cgc.sgot == NULL)
	    {
	      if (htab->cgc.dynobj == NULL)
		htab->cgc.dynobj = abfd;
	      if (!create_got_section (htab->cgc.dynobj, info))
		return FALSE;
	    }
	}

      if (h != NULL)
	{
	  if (htab->cgc.dynobj == NULL)
	    htab->cgc.dynobj = abfd;
	  if (!s390_cgc_create_ifunc_sections (htab->cgc.dynobj, info))
	    return FALSE;

	  /* Make sure an IFUNC symbol defined in a non-shared object
	     always gets a PLT slot.  */
	  if (s390_is_ifunc_symbol_p (h) && h->def_regular)
	    {
	      /* The symbol is called by the dynamic loader in order
		 to resolve the relocation.  So it is in fact also
		 referenced.  */
	      h->ref_regular = 1;
	      h->needs_plt = 1;
	    }
	}

      switch (r_type)
	{
	case R_390_GOTOFF16:
	case R_390_GOTOFF32:
	case R_390_GOTOFF64:
	case R_390_GOTPC:
	case R_390_GOTPCDBL:
	  /* These relocs do not need a GOT slot.  They just load the
	     GOT pointer itself or address something else relative to
	     the GOT.  Since the GOT pointer has been set up above we
	     are done.  */
	  break;

	case R_390_PLT12DBL:
	case R_390_PLT16DBL:
	case R_390_PLT24DBL:
	case R_390_PLT32:
	case R_390_PLT32DBL:
	case R_390_PLT64:
	case R_390_PLTOFF16:
	case R_390_PLTOFF32:
	case R_390_PLTOFF64:
	  /* This symbol requires a procedure linkage table entry.  We
	     actually build the entry in adjust_dynamic_symbol,
	     because this might be a case of linking PIC code which is
	     never referenced by a dynamic object, in which case we
	     don't need to generate a procedure linkage table entry
	     after all.  */

	  /* If this is a local symbol, we resolve it directly without
	     creating a procedure linkage table entry.  */
	  if (h != NULL)
	    {
	      h->needs_plt = 1;
	      h->plt.refcount += 1;
	    }
	  break;

	case R_390_GOTPLT12:
	case R_390_GOTPLT16:
	case R_390_GOTPLT20:
	case R_390_GOTPLT32:
	case R_390_GOTPLT64:
	case R_390_GOTPLTENT:
	  /* This symbol requires either a procedure linkage table entry
	     or an entry in the local got. We actually build the entry
	     in adjust_dynamic_symbol because whether this is really a
	     global reference can change and with it the fact if we have
	     to create a plt entry or a local got entry. To be able to
	     make a once global symbol a local one we have to keep track
	     of the number of gotplt references that exist for this
	     symbol.  */
	  if (h != NULL)
	    {
	      ((struct cgc_s390_link_hash_entry *) h)->gotplt_refcount++;
	      h->needs_plt = 1;
	      h->plt.refcount += 1;
	    }
	  else
	    local_got_refcounts[r_symndx] += 1;
	  break;

	case R_390_TLS_LDM64:
	  htab->tls_ldm_got.refcount += 1;
	  break;

	case R_390_TLS_IE64:
	case R_390_TLS_GOTIE12:
	case R_390_TLS_GOTIE20:
	case R_390_TLS_GOTIE64:
	case R_390_TLS_IEENT:
	  if (info->shared)
	    info->flags |= DF_STATIC_TLS;
	  /* Fall through */

	case R_390_GOT12:
	case R_390_GOT16:
	case R_390_GOT20:
	case R_390_GOT32:
	case R_390_GOT64:
	case R_390_GOTENT:
	case R_390_TLS_GD64:
	  /* This symbol requires a global offset table entry.  */
	  switch (r_type)
	    {
	    default:
	    case R_390_GOT12:
	    case R_390_GOT16:
	    case R_390_GOT20:
	    case R_390_GOT32:
	    case R_390_GOTENT:
	      tls_type = GOT_NORMAL;
	      break;
	    case R_390_TLS_GD64:
	      tls_type = GOT_TLS_GD;
	      break;
	    case R_390_TLS_IE64:
	    case R_390_TLS_GOTIE64:
	      tls_type = GOT_TLS_IE;
	      break;
	    case R_390_TLS_GOTIE12:
	    case R_390_TLS_GOTIE20:
	    case R_390_TLS_IEENT:
	      tls_type = GOT_TLS_IE_NLT;
	      break;
	    }

	  if (h != NULL)
	    {
	      h->got.refcount += 1;
	      old_tls_type = cgc_s390_hash_entry(h)->tls_type;
	    }
	  else
	    {
	      local_got_refcounts[r_symndx] += 1;
	      old_tls_type = cgc_s390_local_got_tls_type (abfd) [r_symndx];
	    }
	  /* If a TLS symbol is accessed using IE at least once,
	     there is no point to use dynamic model for it.  */
	  if (old_tls_type != tls_type && old_tls_type != GOT_UNKNOWN)
	    {
	      if (old_tls_type == GOT_NORMAL || tls_type == GOT_NORMAL)
		{
		  (*_bfd_error_handler)
		    (_("%B: `%s' accessed both as normal and thread local symbol"),
		     abfd, h->root.root.string);
		  return FALSE;
		}
	      if (old_tls_type > tls_type)
		tls_type = old_tls_type;
	    }

	  if (old_tls_type != tls_type)
	    {
	      if (h != NULL)
		cgc_s390_hash_entry (h)->tls_type = tls_type;
	      else
		cgc_s390_local_got_tls_type (abfd) [r_symndx] = tls_type;
	    }

	  if (r_type != R_390_TLS_IE64)
	    break;
	  /* Fall through */

	case R_390_TLS_LE64:
	  if (!info->shared)
	    break;
	  info->flags |= DF_STATIC_TLS;
	  /* Fall through */

	case R_390_8:
	case R_390_16:
	case R_390_32:
	case R_390_64:
	case R_390_PC12DBL:
	case R_390_PC16:
	case R_390_PC16DBL:
	case R_390_PC24DBL:
	case R_390_PC32:
	case R_390_PC32DBL:
	case R_390_PC64:
	  if (h != NULL)
	    {
	      /* If this reloc is in a read-only section, we might
		 need a copy reloc.  We can't check reliably at this
		 stage whether the section is read-only, as input
		 sections have not yet been mapped to output sections.
		 Tentatively set the flag for now, and correct in
		 adjust_dynamic_symbol.  */
	      h->non_got_ref = 1;

	      if (!info->shared)
		{
		  /* We may need a .plt entry if the function this reloc
		     refers to is in a shared lib.  */
		  h->plt.refcount += 1;
		}
	    }

	  /* If we are creating a shared library, and this is a reloc
	     against a global symbol, or a non PC relative reloc
	     against a local symbol, then we need to copy the reloc
	     into the shared library.  However, if we are linking with
	     -Bsymbolic, we do not need to copy a reloc against a
	     global symbol which is defined in an object we are
	     including in the link (i.e., DEF_REGULAR is set).  At
	     this point we have not seen all the input files, so it is
	     possible that DEF_REGULAR is not set now but will be set
	     later (it is never cleared).  In case of a weak definition,
	     DEF_REGULAR may be cleared later by a strong definition in
	     a shared library. We account for that possibility below by
	     storing information in the relocs_copied field of the hash
	     table entry.  A similar situation occurs when creating
	     shared libraries and symbol visibility changes render the
	     symbol local.

	     If on the other hand, we are creating an executable, we
	     may need to keep relocations for symbols satisfied by a
	     dynamic library if we manage to avoid copy relocs for the
	     symbol.  */
	  if ((info->shared
	       && (sec->flags & SEC_ALLOC) != 0
	       && ((CGC64_R_TYPE (rel->r_info) != R_390_PC16
		    && CGC64_R_TYPE (rel->r_info) != R_390_PC12DBL
		    && CGC64_R_TYPE (rel->r_info) != R_390_PC16DBL
		    && CGC64_R_TYPE (rel->r_info) != R_390_PC24DBL
		    && CGC64_R_TYPE (rel->r_info) != R_390_PC32
		    && CGC64_R_TYPE (rel->r_info) != R_390_PC32DBL
		    && CGC64_R_TYPE (rel->r_info) != R_390_PC64)
		   || (h != NULL
		       && (! SYMBOLIC_BIND (info, h)
			   || h->root.type == bfd_link_hash_defweak
			   || !h->def_regular))))
	      || (ELIMINATE_COPY_RELOCS
		  && !info->shared
		  && (sec->flags & SEC_ALLOC) != 0
		  && h != NULL
		  && (h->root.type == bfd_link_hash_defweak
		      || !h->def_regular)))
	    {
	      struct cgc_dyn_relocs *p;
	      struct cgc_dyn_relocs **head;

	      /* We must copy these reloc types into the output file.
		 Create a reloc section in dynobj and make room for
		 this reloc.  */
	      if (sreloc == NULL)
		{
		  if (htab->cgc.dynobj == NULL)
		    htab->cgc.dynobj = abfd;

		  sreloc = _bfd_cgc_make_dynamic_reloc_section
		    (sec, htab->cgc.dynobj, 3, abfd, /*rela?*/ TRUE);

		  if (sreloc == NULL)
		    return FALSE;
		}

	      /* If this is a global symbol, we count the number of
		 relocations we need for this symbol.  */
	      if (h != NULL)
		{
		  head = &((struct cgc_s390_link_hash_entry *) h)->dyn_relocs;
		}
	      else
		{
		  /* Track dynamic relocs needed for local syms too.
		     We really need local syms available to do this
		     easily.  Oh well.  */
		  asection *s;
		  void *vpp;

		  isym = bfd_sym_from_r_symndx (&htab->sym_cache,
						abfd, r_symndx);
		  if (isym == NULL)
		    return FALSE;

		  s = bfd_section_from_cgc_index (abfd, isym->st_shndx);
		  if (s == NULL)
		    s = sec;

		  vpp = &cgc_section_data (s)->local_dynrel;
		  head = (struct cgc_dyn_relocs **) vpp;
		}

	      p = *head;
	      if (p == NULL || p->sec != sec)
		{
		  bfd_size_type amt = sizeof *p;
		  p = ((struct cgc_dyn_relocs *)
		       bfd_alloc (htab->cgc.dynobj, amt));
		  if (p == NULL)
		    return FALSE;
		  p->next = *head;
		  *head = p;
		  p->sec = sec;
		  p->count = 0;
		  p->pc_count = 0;
		}

	      p->count += 1;
	      if (CGC64_R_TYPE (rel->r_info) == R_390_PC16
		  || CGC64_R_TYPE (rel->r_info) == R_390_PC12DBL
		  || CGC64_R_TYPE (rel->r_info) == R_390_PC16DBL
		  || CGC64_R_TYPE (rel->r_info) == R_390_PC16DBL
		  || CGC64_R_TYPE (rel->r_info) == R_390_PC32
		  || CGC64_R_TYPE (rel->r_info) == R_390_PC32DBL
		  || CGC64_R_TYPE (rel->r_info) == R_390_PC64)
		p->pc_count += 1;
	    }
	  break;

	  /* This relocation describes the C++ object vtable hierarchy.
	     Reconstruct it for later use during GC.  */
	case R_390_GNU_VTINHERIT:
	  if (!bfd_cgc_gc_record_vtinherit (abfd, sec, h, rel->r_offset))
	    return FALSE;
	  break;

	  /* This relocation describes which C++ vtable entries are actually
	     used.  Record for later use during GC.  */
	case R_390_GNU_VTENTRY:
	  BFD_ASSERT (h != NULL);
	  if (h != NULL
	      && !bfd_cgc_gc_record_vtentry (abfd, sec, h, rel->r_addend))
	    return FALSE;
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}

/* Return the section that should be marked against GC for a given
   relocation.  */

static asection *
cgc_s390_gc_mark_hook (asection *sec,
		       struct bfd_link_info *info,
		       Cgc_Internal_Rela *rel,
		       struct cgc_link_hash_entry *h,
		       Cgc_Internal_Sym *sym)
{
  if (h != NULL)
    switch (CGC64_R_TYPE (rel->r_info))
      {
      case R_390_GNU_VTINHERIT:
      case R_390_GNU_VTENTRY:
	return NULL;
      }

  return _bfd_cgc_gc_mark_hook (sec, info, rel, h, sym);
}

/* Update the got entry reference counts for the section being removed.  */

static bfd_boolean
cgc_s390_gc_sweep_hook (bfd *abfd,
			struct bfd_link_info *info,
			asection *sec,
			const Cgc_Internal_Rela *relocs)
{
  struct cgc_s390_link_hash_table *htab;
  Cgc_Internal_Shdr *symtab_hdr;
  struct cgc_link_hash_entry **sym_hashes;
  bfd_signed_vma *local_got_refcounts;
  const Cgc_Internal_Rela *rel, *relend;

  if (info->relocatable)
    return TRUE;

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  cgc_section_data (sec)->local_dynrel = NULL;

  symtab_hdr = &cgc_symtab_hdr (abfd);
  sym_hashes = cgc_sym_hashes (abfd);
  local_got_refcounts = cgc_local_got_refcounts (abfd);

  relend = relocs + sec->reloc_count;
  for (rel = relocs; rel < relend; rel++)
    {
      unsigned long r_symndx;
      unsigned int r_type;
      struct cgc_link_hash_entry *h = NULL;

      r_symndx = CGC64_R_SYM (rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  struct cgc_s390_link_hash_entry *eh;
	  struct cgc_dyn_relocs **pp;
	  struct cgc_dyn_relocs *p;

	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct cgc_link_hash_entry *) h->root.u.i.link;
	  eh = (struct cgc_s390_link_hash_entry *) h;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; pp = &p->next)
	    if (p->sec == sec)
	      {
		/* Everything must go for SEC.  */
		*pp = p->next;
		break;
	      }
	}
      else
	{
	  Cgc_Internal_Sym *isym;

	  /* A local symbol.  */
	  isym = bfd_sym_from_r_symndx (&htab->sym_cache,
					abfd, r_symndx);
	  if (isym == NULL)
	    return FALSE;

	  if (CGC_ST_TYPE (isym->st_info) == STT_GNU_IFUNC)
	    {
	      struct plt_entry *plt = cgc_s390_local_plt (abfd);
	      if (plt[r_symndx].plt.refcount > 0)
		plt[r_symndx].plt.refcount--;
	    }
	}

      r_type = CGC64_R_TYPE (rel->r_info);
      r_type = cgc_s390_tls_transition (info, r_type, h != NULL);
      switch (r_type)
	{
	case R_390_TLS_LDM64:
	  if (htab->tls_ldm_got.refcount > 0)
	    htab->tls_ldm_got.refcount -= 1;
	  break;

	case R_390_TLS_GD64:
	case R_390_TLS_IE64:
	case R_390_TLS_GOTIE12:
	case R_390_TLS_GOTIE20:
	case R_390_TLS_GOTIE64:
	case R_390_TLS_IEENT:
	case R_390_GOT12:
	case R_390_GOT16:
	case R_390_GOT20:
	case R_390_GOT32:
	case R_390_GOT64:
	case R_390_GOTOFF16:
	case R_390_GOTOFF32:
	case R_390_GOTOFF64:
	case R_390_GOTPC:
	case R_390_GOTPCDBL:
	case R_390_GOTENT:
	  if (h != NULL)
	    {
	      if (h->got.refcount > 0)
		h->got.refcount -= 1;
	    }
	  else if (local_got_refcounts != NULL)
	    {
	      if (local_got_refcounts[r_symndx] > 0)
		local_got_refcounts[r_symndx] -= 1;
	    }
	  break;

	case R_390_8:
	case R_390_12:
	case R_390_16:
	case R_390_20:
	case R_390_32:
	case R_390_64:
	case R_390_PC16:
	case R_390_PC12DBL:
	case R_390_PC16DBL:
	case R_390_PC24DBL:
	case R_390_PC32:
	case R_390_PC32DBL:
	case R_390_PC64:
	  if (info->shared)
	    break;
	  /* Fall through */

	case R_390_PLT12DBL:
	case R_390_PLT16DBL:
	case R_390_PLT24DBL:
	case R_390_PLT32:
	case R_390_PLT32DBL:
	case R_390_PLT64:
	case R_390_PLTOFF16:
	case R_390_PLTOFF32:
	case R_390_PLTOFF64:
	  if (h != NULL)
	    {
	      if (h->plt.refcount > 0)
		h->plt.refcount -= 1;
	    }
	  break;

	case R_390_GOTPLT12:
	case R_390_GOTPLT16:
	case R_390_GOTPLT20:
	case R_390_GOTPLT32:
	case R_390_GOTPLT64:
	case R_390_GOTPLTENT:
	  if (h != NULL)
	    {
	      if (h->plt.refcount > 0)
		{
		  ((struct cgc_s390_link_hash_entry *) h)->gotplt_refcount--;
		  h->plt.refcount -= 1;
		}
	    }
	  else if (local_got_refcounts != NULL)
	    {
	      if (local_got_refcounts[r_symndx] > 0)
		local_got_refcounts[r_symndx] -= 1;
	    }
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}

/* Make sure we emit a GOT entry if the symbol was supposed to have a PLT
   entry but we found we will not create any.  Called when we find we will
   not have any PLT for this symbol, by for example
   cgc_s390_adjust_dynamic_symbol when we're doing a proper dynamic link,
   or cgc_s390_size_dynamic_sections if no dynamic sections will be
   created (we're only linking static objects).  */

static void
cgc_s390_adjust_gotplt (struct cgc_s390_link_hash_entry *h)
{
  if (h->cgc.root.type == bfd_link_hash_warning)
    h = (struct cgc_s390_link_hash_entry *) h->cgc.root.u.i.link;

  if (h->gotplt_refcount <= 0)
    return;

  /* We simply add the number of gotplt references to the number
   * of got references for this symbol.  */
  h->cgc.got.refcount += h->gotplt_refcount;
  h->gotplt_refcount = -1;
}

/* Adjust a symbol defined by a dynamic object and referenced by a
   regular object.  The current definition is in some section of the
   dynamic object, but we're not including those sections.  We have to
   change the definition to something the rest of the link can
   understand.  */

static bfd_boolean
cgc_s390_adjust_dynamic_symbol (struct bfd_link_info *info,
				struct cgc_link_hash_entry *h)
{
  struct cgc_s390_link_hash_table *htab;
  asection *s;

  /* STT_GNU_IFUNC symbol must go through PLT. */
  if (s390_is_ifunc_symbol_p (h))
    return TRUE;

  /* If this is a function, put it in the procedure linkage table.  We
     will fill in the contents of the procedure linkage table later
     (although we could actually do it here).  */
  if (h->type == STT_FUNC
      || h->needs_plt)
    {
      if (h->plt.refcount <= 0
	  || SYMBOL_CALLS_LOCAL (info, h)
	  || (CGC_ST_VISIBILITY (h->other) != STV_DEFAULT
	      && h->root.type == bfd_link_hash_undefweak))
	{
	  /* This case can occur if we saw a PLT32 reloc in an input
	     file, but the symbol was never referred to by a dynamic
	     object, or if all references were garbage collected.  In
	     such a case, we don't actually need to build a procedure
	     linkage table, and we can just do a PC32 reloc instead.  */
	  h->plt.offset = (bfd_vma) -1;
	  h->needs_plt = 0;
	  cgc_s390_adjust_gotplt((struct cgc_s390_link_hash_entry *) h);
	}

      return TRUE;
    }
  else
    /* It's possible that we incorrectly decided a .plt reloc was
       needed for an R_390_PC32 reloc to a non-function sym in
       check_relocs.  We can't decide accurately between function and
       non-function syms in check-relocs;  Objects loaded later in
       the link may change h->type.  So fix it now.  */
    h->plt.offset = (bfd_vma) -1;

  /* If this is a weak symbol, and there is a real definition, the
     processor independent code will have arranged for us to see the
     real definition first, and we can just use the same value.  */
  if (h->u.weakdef != NULL)
    {
      BFD_ASSERT (h->u.weakdef->root.type == bfd_link_hash_defined
		  || h->u.weakdef->root.type == bfd_link_hash_defweak);
      h->root.u.def.section = h->u.weakdef->root.u.def.section;
      h->root.u.def.value = h->u.weakdef->root.u.def.value;
      if (ELIMINATE_COPY_RELOCS || info->nocopyreloc)
	h->non_got_ref = h->u.weakdef->non_got_ref;
      return TRUE;
    }

  /* This is a reference to a symbol defined by a dynamic object which
     is not a function.  */

  /* If we are creating a shared library, we must presume that the
     only references to the symbol are via the global offset table.
     For such cases we need not do anything here; the relocations will
     be handled correctly by relocate_section.  */
  if (info->shared)
    return TRUE;

  /* If there are no references to this symbol that do not use the
     GOT, we don't need to generate a copy reloc.  */
  if (!h->non_got_ref)
    return TRUE;

  /* If -z nocopyreloc was given, we won't generate them either.  */
  if (info->nocopyreloc)
    {
      h->non_got_ref = 0;
      return TRUE;
    }

  if (ELIMINATE_COPY_RELOCS)
    {
      struct cgc_s390_link_hash_entry * eh;
      struct cgc_dyn_relocs *p;

      eh = (struct cgc_s390_link_hash_entry *) h;
      for (p = eh->dyn_relocs; p != NULL; p = p->next)
	{
	  s = p->sec->output_section;
	  if (s != NULL && (s->flags & SEC_READONLY) != 0)
	    break;
	}

      /* If we didn't find any dynamic relocs in read-only sections, then
	 we'll be keeping the dynamic relocs and avoiding the copy reloc.  */
      if (p == NULL)
	{
	  h->non_got_ref = 0;
	  return TRUE;
	}
    }

  /* We must allocate the symbol in our .dynbss section, which will
     become part of the .bss section of the executable.  There will be
     an entry for this symbol in the .dynsym section.  The dynamic
     object will contain position independent code, so all references
     from the dynamic object to this symbol will go through the global
     offset table.  The dynamic linker will use the .dynsym entry to
     determine the address it must put in the global offset table, so
     both the dynamic object and the regular object will refer to the
     same memory location for the variable.  */

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  /* We must generate a R_390_COPY reloc to tell the dynamic linker to
     copy the initial value out of the dynamic object and into the
     runtime process image.  */
  if ((h->root.u.def.section->flags & SEC_ALLOC) != 0 && h->size != 0)
    {
      htab->srelbss->size += sizeof (Cgc64_External_Rela);
      h->needs_copy = 1;
    }

  s = htab->sdynbss;

  return _bfd_cgc_adjust_dynamic_copy (h, s);
}

/* Allocate space in .plt, .got and associated reloc sections for
   dynamic relocs.  */

static bfd_boolean
allocate_dynrelocs (struct cgc_link_hash_entry *h,
		    void * inf)
{
  struct bfd_link_info *info;
  struct cgc_s390_link_hash_table *htab;
  struct cgc_s390_link_hash_entry *eh = (struct cgc_s390_link_hash_entry *)h;
  struct cgc_dyn_relocs *p;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  info = (struct bfd_link_info *) inf;
  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  /* Since STT_GNU_IFUNC symbol must go through PLT, we handle it
     here if it is defined and referenced in a non-shared object.  */
  if (s390_is_ifunc_symbol_p (h) && h->def_regular)
    return s390_cgc_allocate_ifunc_dyn_relocs (info, h,
					       &eh->dyn_relocs);
  else if (htab->cgc.dynamic_sections_created
	   && h->plt.refcount > 0)
    {
      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_cgc_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      if (info->shared
	  || WILL_CALL_FINISH_DYNAMIC_SYMBOL (1, 0, h))
	{
	  asection *s = htab->cgc.splt;

	  /* If this is the first .plt entry, make room for the special
	     first entry.  */
	  if (s->size == 0)
	    s->size += PLT_FIRST_ENTRY_SIZE;

	  h->plt.offset = s->size;

	  /* If this symbol is not defined in a regular file, and we are
	     not generating a shared library, then set the symbol to this
	     location in the .plt.  This is required to make function
	     pointers compare as equal between the normal executable and
	     the shared library.  */
	  if (! info->shared
	      && !h->def_regular)
	    {
	      h->root.u.def.section = s;
	      h->root.u.def.value = h->plt.offset;
	    }

	  /* Make room for this entry.  */
	  s->size += PLT_ENTRY_SIZE;

	  /* We also need to make an entry in the .got.plt section, which
	     will be placed in the .got section by the linker script.  */
	  htab->cgc.sgotplt->size += GOT_ENTRY_SIZE;

	  /* We also need to make an entry in the .rela.plt section.  */
	  htab->cgc.srelplt->size += sizeof (Cgc64_External_Rela);
	}
      else
	{
	  h->plt.offset = (bfd_vma) -1;
	  h->needs_plt = 0;
	  cgc_s390_adjust_gotplt((struct cgc_s390_link_hash_entry *) h);
	}
    }
  else
    {
      h->plt.offset = (bfd_vma) -1;
      h->needs_plt = 0;
      cgc_s390_adjust_gotplt((struct cgc_s390_link_hash_entry *) h);
    }

  /* If R_390_TLS_{IE64,GOTIE64,GOTIE12,IEENT} symbol is now local to
     the binary, we can optimize a bit. IE64 and GOTIE64 get converted
     to R_390_TLS_LE64 requiring no TLS entry. For GOTIE12 and IEENT
     we can save the dynamic TLS relocation.  */
  if (h->got.refcount > 0
      && !info->shared
      && h->dynindx == -1
      && cgc_s390_hash_entry(h)->tls_type >= GOT_TLS_IE)
    {
      if (cgc_s390_hash_entry(h)->tls_type == GOT_TLS_IE_NLT)
	/* For the GOTIE access without a literal pool entry the offset has
	   to be stored somewhere. The immediate value in the instruction
	   is not bit enough so the value is stored in the got.  */
	{
	  h->got.offset = htab->cgc.sgot->size;
	  htab->cgc.sgot->size += GOT_ENTRY_SIZE;
	}
      else
	h->got.offset = (bfd_vma) -1;
    }
  else if (h->got.refcount > 0)
    {
      asection *s;
      bfd_boolean dyn;
      int tls_type = cgc_s390_hash_entry(h)->tls_type;

      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_cgc_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      s = htab->cgc.sgot;
      h->got.offset = s->size;
      s->size += GOT_ENTRY_SIZE;
      /* R_390_TLS_GD64 needs 2 consecutive GOT slots.  */
      if (tls_type == GOT_TLS_GD)
	s->size += GOT_ENTRY_SIZE;
      dyn = htab->cgc.dynamic_sections_created;
      /* R_390_TLS_IE64 needs one dynamic relocation,
	 R_390_TLS_GD64 needs one if local symbol and two if global.  */
      if ((tls_type == GOT_TLS_GD && h->dynindx == -1)
	  || tls_type >= GOT_TLS_IE)
	htab->cgc.srelgot->size += sizeof (Cgc64_External_Rela);
      else if (tls_type == GOT_TLS_GD)
	htab->cgc.srelgot->size += 2 * sizeof (Cgc64_External_Rela);
      else if ((CGC_ST_VISIBILITY (h->other) == STV_DEFAULT
		|| h->root.type != bfd_link_hash_undefweak)
	       && (info->shared
		   || WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, 0, h)))
	htab->cgc.srelgot->size += sizeof (Cgc64_External_Rela);
    }
  else
    h->got.offset = (bfd_vma) -1;

  if (eh->dyn_relocs == NULL)
    return TRUE;

  /* In the shared -Bsymbolic case, discard space allocated for
     dynamic pc-relative relocs against symbols which turn out to be
     defined in regular objects.  For the normal shared case, discard
     space for pc-relative relocs that have become local due to symbol
     visibility changes.  */

  if (info->shared)
    {
      if (SYMBOL_CALLS_LOCAL (info, h))
	{
	  struct cgc_dyn_relocs **pp;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; )
	    {
	      p->count -= p->pc_count;
	      p->pc_count = 0;
	      if (p->count == 0)
		*pp = p->next;
	      else
		pp = &p->next;
	    }
	}

      /* Also discard relocs on undefined weak syms with non-default
	 visibility.  */
      if (eh->dyn_relocs != NULL
	  && h->root.type == bfd_link_hash_undefweak)
	{
	  if (CGC_ST_VISIBILITY (h->other) != STV_DEFAULT)
	    eh->dyn_relocs = NULL;

	  /* Make sure undefined weak symbols are output as a dynamic
	     symbol in PIEs.  */
	  else if (h->dynindx == -1
		   && !h->forced_local)
	    {
	      if (! bfd_cgc_link_record_dynamic_symbol (info, h))
		return FALSE;
	    }
	}
    }
  else if (ELIMINATE_COPY_RELOCS)
    {
      /* For the non-shared case, discard space for relocs against
	 symbols which turn out to need copy relocs or are not
	 dynamic.  */

      if (!h->non_got_ref
	  && ((h->def_dynamic
	       && !h->def_regular)
	      || (htab->cgc.dynamic_sections_created
		  && (h->root.type == bfd_link_hash_undefweak
		      || h->root.type == bfd_link_hash_undefined))))
	{
	  /* Make sure this symbol is output as a dynamic symbol.
	     Undefined weak syms won't yet be marked as dynamic.  */
	  if (h->dynindx == -1
	      && !h->forced_local)
	    {
	      if (! bfd_cgc_link_record_dynamic_symbol (info, h))
		return FALSE;
	    }

	  /* If that succeeded, we know we'll be keeping all the
	     relocs.  */
	  if (h->dynindx != -1)
	    goto keep;
	}

      eh->dyn_relocs = NULL;

    keep: ;
    }

  /* Finally, allocate space.  */
  for (p = eh->dyn_relocs; p != NULL; p = p->next)
    {
      asection *sreloc = cgc_section_data (p->sec)->sreloc;
      sreloc->size += p->count * sizeof (Cgc64_External_Rela);
    }

  return TRUE;
}

/* Find any dynamic relocs that apply to read-only sections.  */

static bfd_boolean
readonly_dynrelocs (struct cgc_link_hash_entry *h, void * inf)
{
  struct cgc_s390_link_hash_entry *eh;
  struct cgc_dyn_relocs *p;

  eh = (struct cgc_s390_link_hash_entry *) h;
  for (p = eh->dyn_relocs; p != NULL; p = p->next)
    {
      asection *s = p->sec->output_section;

      if (s != NULL && (s->flags & SEC_READONLY) != 0)
	{
	  struct bfd_link_info *info = (struct bfd_link_info *) inf;

	  info->flags |= DF_TEXTREL;

	  /* Not an error, just cut short the traversal.  */
	  return FALSE;
	}
    }
  return TRUE;
}

/* Set the sizes of the dynamic sections.  */

static bfd_boolean
cgc_s390_size_dynamic_sections (bfd *output_bfd ATTRIBUTE_UNUSED,
				struct bfd_link_info *info)
{
  struct cgc_s390_link_hash_table *htab;
  bfd *dynobj;
  asection *s;
  bfd_boolean relocs;
  bfd *ibfd;

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  dynobj = htab->cgc.dynobj;
  if (dynobj == NULL)
    abort ();

  if (htab->cgc.dynamic_sections_created)
    {
      /* Set the contents of the .interp section to the interpreter.  */
      if (info->executable)
	{
	  s = bfd_get_linker_section (dynobj, ".interp");
	  if (s == NULL)
	    abort ();
	  s->size = sizeof CGC_DYNAMIC_INTERPRETER;
	  s->contents = (unsigned char *) CGC_DYNAMIC_INTERPRETER;
	}
    }

  /* Set up .got offsets for local syms, and space for local dynamic
     relocs.  */
  for (ibfd = info->input_bfds; ibfd != NULL; ibfd = ibfd->link_next)
    {
      bfd_signed_vma *local_got;
      bfd_signed_vma *end_local_got;
      char *local_tls_type;
      bfd_size_type locsymcount;
      Cgc_Internal_Shdr *symtab_hdr;
      asection *srela;
      struct plt_entry *local_plt;
      unsigned int i;

      if (! is_s390_cgc (ibfd))
	continue;

      for (s = ibfd->sections; s != NULL; s = s->next)
	{
	  struct cgc_dyn_relocs *p;

	  for (p = cgc_section_data (s)->local_dynrel; p != NULL; p = p->next)
	    {
	      if (!bfd_is_abs_section (p->sec)
		  && bfd_is_abs_section (p->sec->output_section))
		{
		  /* Input section has been discarded, either because
		     it is a copy of a linkonce section or due to
		     linker script /DISCARD/, so we'll be discarding
		     the relocs too.  */
		}
	      else if (p->count != 0)
		{
		  srela = cgc_section_data (p->sec)->sreloc;
		  srela->size += p->count * sizeof (Cgc64_External_Rela);
		  if ((p->sec->output_section->flags & SEC_READONLY) != 0)
		    info->flags |= DF_TEXTREL;
		}
	    }
	}

      local_got = cgc_local_got_refcounts (ibfd);
      if (!local_got)
	continue;

      symtab_hdr = &cgc_symtab_hdr (ibfd);
      locsymcount = symtab_hdr->sh_info;
      end_local_got = local_got + locsymcount;
      local_tls_type = cgc_s390_local_got_tls_type (ibfd);
      s = htab->cgc.sgot;
      srela = htab->cgc.srelgot;
      for (; local_got < end_local_got; ++local_got, ++local_tls_type)
	{
	  if (*local_got > 0)
	    {
	      *local_got = s->size;
	      s->size += GOT_ENTRY_SIZE;
	      if (*local_tls_type == GOT_TLS_GD)
		s->size += GOT_ENTRY_SIZE;
	      if (info->shared)
		srela->size += sizeof (Cgc64_External_Rela);
	    }
	  else
	    *local_got = (bfd_vma) -1;
	}

      local_plt = cgc_s390_local_plt (ibfd);
      for (i = 0; i < symtab_hdr->sh_info; i++)
	{
	  if (local_plt[i].plt.refcount > 0)
	    {
	      local_plt[i].plt.offset = htab->cgc.iplt->size;
	      htab->cgc.iplt->size += PLT_ENTRY_SIZE;
	      htab->cgc.igotplt->size += GOT_ENTRY_SIZE;
	      htab->cgc.irelplt->size += sizeof (Cgc64_External_Rela);
	    }
	  else
	    local_plt[i].plt.offset = (bfd_vma) -1;
	}
    }

  if (htab->tls_ldm_got.refcount > 0)
    {
      /* Allocate 2 got entries and 1 dynamic reloc for R_390_TLS_LDM64
	 relocs.  */
      htab->tls_ldm_got.offset = htab->cgc.sgot->size;
      htab->cgc.sgot->size += 2 * GOT_ENTRY_SIZE;
      htab->cgc.srelgot->size += sizeof (Cgc64_External_Rela);
    }
  else
    htab->tls_ldm_got.offset = -1;

  /* Allocate global sym .plt and .got entries, and space for global
     sym dynamic relocs.  */
  cgc_link_hash_traverse (&htab->cgc, allocate_dynrelocs, info);

  /* We now have determined the sizes of the various dynamic sections.
     Allocate memory for them.  */
  relocs = FALSE;
  for (s = dynobj->sections; s != NULL; s = s->next)
    {
      if ((s->flags & SEC_LINKER_CREATED) == 0)
	continue;

      if (s == htab->cgc.splt
	  || s == htab->cgc.sgot
	  || s == htab->cgc.sgotplt
	  || s == htab->sdynbss
	  || s == htab->cgc.iplt
	  || s == htab->cgc.igotplt
	  || s == htab->irelifunc)
	{
	  /* Strip this section if we don't need it; see the
	     comment below.  */
	}
      else if (CONST_STRNEQ (bfd_get_section_name (dynobj, s), ".rela"))
	{
	  if (s->size != 0 && s != htab->cgc.srelplt)
	    relocs = TRUE;

	  /* We use the reloc_count field as a counter if we need
	     to copy relocs into the output file.  */
	  s->reloc_count = 0;
	}
      else
	{
	  /* It's not one of our sections, so don't allocate space.  */
	  continue;
	}

      if (s->size == 0)
	{
	  /* If we don't need this section, strip it from the
	     output file.  This is to handle .rela.bss and
	     .rela.plt.  We must create it in
	     create_dynamic_sections, because it must be created
	     before the linker maps input sections to output
	     sections.  The linker does that before
	     adjust_dynamic_symbol is called, and it is that
	     function which decides whether anything needs to go
	     into these sections.  */

	  s->flags |= SEC_EXCLUDE;
	  continue;
	}

      if ((s->flags & SEC_HAS_CONTENTS) == 0)
	continue;

      /* Allocate memory for the section contents.  We use bfd_zalloc
	 here in case unused entries are not reclaimed before the
	 section's contents are written out.  This should not happen,
	 but this way if it does, we get a R_390_NONE reloc instead
	 of garbage.  */
      s->contents = (bfd_byte *) bfd_zalloc (dynobj, s->size);
      if (s->contents == NULL)
	return FALSE;
    }

  if (htab->cgc.dynamic_sections_created)
    {
      /* Add some entries to the .dynamic section.  We fill in the
	 values later, in cgc_s390_finish_dynamic_sections, but we
	 must add the entries now so that we get the correct size for
	 the .dynamic section.  The DT_DEBUG entry is filled in by the
	 dynamic linker and used by the debugger.  */
#define add_dynamic_entry(TAG, VAL) \
  _bfd_cgc_add_dynamic_entry (info, TAG, VAL)

      if (info->executable)
	{
	  if (!add_dynamic_entry (DT_DEBUG, 0))
	    return FALSE;
	}

      if (htab->cgc.splt->size != 0)
	{
	  if (!add_dynamic_entry (DT_PLTGOT, 0)
	      || !add_dynamic_entry (DT_PLTRELSZ, 0)
	      || !add_dynamic_entry (DT_PLTREL, DT_RELA)
	      || !add_dynamic_entry (DT_JMPREL, 0))
	    return FALSE;
	}

      if (relocs)
	{
	  if (!add_dynamic_entry (DT_RELA, 0)
	      || !add_dynamic_entry (DT_RELASZ, 0)
	      || !add_dynamic_entry (DT_RELAENT, sizeof (Cgc64_External_Rela)))
	    return FALSE;

	  /* If any dynamic relocs apply to a read-only section,
	     then we need a DT_TEXTREL entry.  */
	  if ((info->flags & DF_TEXTREL) == 0)
	    cgc_link_hash_traverse (&htab->cgc, readonly_dynrelocs,
				    info);

	  if ((info->flags & DF_TEXTREL) != 0)
	    {
	      if (!add_dynamic_entry (DT_TEXTREL, 0))
		return FALSE;
	    }
	}
    }
#undef add_dynamic_entry

  return TRUE;
}

/* Return the base VMA address which should be subtracted from real addresses
   when resolving @dtpoff relocation.
   This is PT_TLS segment p_vaddr.  */

static bfd_vma
dtpoff_base (struct bfd_link_info *info)
{
  /* If tls_sec is NULL, we should have signalled an error already.  */
  if (cgc_hash_table (info)->tls_sec == NULL)
    return 0;
  return cgc_hash_table (info)->tls_sec->vma;
}

/* Return the relocation value for @tpoff relocation
   if STT_TLS virtual address is ADDRESS.  */

static bfd_vma
tpoff (struct bfd_link_info *info, bfd_vma address)
{
  struct cgc_link_hash_table *htab = cgc_hash_table (info);

  /* If tls_sec is NULL, we should have signalled an error already.  */
  if (htab->tls_sec == NULL)
    return 0;
  return htab->tls_size + htab->tls_sec->vma - address;
}

/* Complain if TLS instruction relocation is against an invalid
   instruction.  */

static void
invalid_tls_insn (bfd *input_bfd,
		  asection *input_section,
		  Cgc_Internal_Rela *rel)
{
  reloc_howto_type *howto;

  howto = cgc_howto_table + CGC64_R_TYPE (rel->r_info);
  (*_bfd_error_handler)
    (_("%B(%A+0x%lx): invalid instruction for TLS relocation %s"),
     input_bfd,
     input_section,
     (long) rel->r_offset,
     howto->name);
  bfd_set_error (bfd_error_bad_value);
}

/* Relocate a 390 CGC section.  */

static bfd_boolean
cgc_s390_relocate_section (bfd *output_bfd,
			   struct bfd_link_info *info,
			   bfd *input_bfd,
			   asection *input_section,
			   bfd_byte *contents,
			   Cgc_Internal_Rela *relocs,
			   Cgc_Internal_Sym *local_syms,
			   asection **local_sections)
{
  struct cgc_s390_link_hash_table *htab;
  Cgc_Internal_Shdr *symtab_hdr;
  struct cgc_link_hash_entry **sym_hashes;
  bfd_vma *local_got_offsets;
  Cgc_Internal_Rela *rel;
  Cgc_Internal_Rela *relend;

  BFD_ASSERT (is_s390_cgc (input_bfd));

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  symtab_hdr = &cgc_symtab_hdr (input_bfd);
  sym_hashes = cgc_sym_hashes (input_bfd);
  local_got_offsets = cgc_local_got_offsets (input_bfd);

  rel = relocs;
  relend = relocs + input_section->reloc_count;
  for (; rel < relend; rel++)
    {
      unsigned int r_type;
      reloc_howto_type *howto;
      unsigned long r_symndx;
      struct cgc_link_hash_entry *h;
      Cgc_Internal_Sym *sym;
      asection *sec;
      bfd_vma off;
      bfd_vma relocation;
      bfd_boolean unresolved_reloc;
      bfd_reloc_status_type r;
      int tls_type;
      asection *base_got = htab->cgc.sgot;

      r_type = CGC64_R_TYPE (rel->r_info);
      if (r_type == (int) R_390_GNU_VTINHERIT
	  || r_type == (int) R_390_GNU_VTENTRY)
	continue;
      if (r_type >= (int) R_390_max)
	{
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}

      howto = cgc_howto_table + r_type;
      r_symndx = CGC64_R_SYM (rel->r_info);

      h = NULL;
      sym = NULL;
      sec = NULL;
      unresolved_reloc = FALSE;
      if (r_symndx < symtab_hdr->sh_info)
	{
	  sym = local_syms + r_symndx;
	  sec = local_sections[r_symndx];

	  if (CGC_ST_TYPE (sym->st_info) == STT_GNU_IFUNC)
	    {
	      struct plt_entry *local_plt = cgc_s390_local_plt (input_bfd);
	      if (local_plt == NULL)
		return FALSE;

	      /* Address of the PLT slot.  */
	      relocation = (htab->cgc.iplt->output_section->vma
			    + htab->cgc.iplt->output_offset
			    + local_plt[r_symndx].plt.offset);

	      switch (r_type)
		{
		case R_390_PLTOFF16:
		case R_390_PLTOFF32:
		case R_390_PLTOFF64:
		  relocation -= htab->cgc.sgot->output_section->vma;
		  break;
		case R_390_GOTPLT12:
		case R_390_GOTPLT16:
		case R_390_GOTPLT20:
		case R_390_GOTPLT32:
		case R_390_GOTPLT64:
		case R_390_GOTPLTENT:
		case R_390_GOT12:
		case R_390_GOT16:
		case R_390_GOT20:
		case R_390_GOT32:
		case R_390_GOT64:
		case R_390_GOTENT:
		  {
		    /* Write the PLT slot address into the GOT slot.  */
		    bfd_put_64 (output_bfd, relocation,
				htab->cgc.sgot->contents +
				local_got_offsets[r_symndx]);
		    relocation = (local_got_offsets[r_symndx] +
				  htab->cgc.sgot->output_offset);

		    if (r_type == R_390_GOTENT || r_type == R_390_GOTPLTENT)
		      relocation += htab->cgc.sgot->output_section->vma;
		    break;
		  }
		default:
		  break;
		}
	      /* The output section is needed later in
		 finish_dynamic_section when creating the dynamic
		 relocation.  */
	      local_plt[r_symndx].sec = sec;
	      goto do_relocation;
	    }
	  else
	    relocation = _bfd_cgc_rela_local_sym (output_bfd, sym, &sec, rel);
	}
      else
	{
	  bfd_boolean warned ATTRIBUTE_UNUSED;

	  RELOC_FOR_GLOBAL_SYMBOL (info, input_bfd, input_section, rel,
				   r_symndx, symtab_hdr, sym_hashes,
				   h, sec, relocation,
				   unresolved_reloc, warned);
	}

      if (sec != NULL && discarded_section (sec))
	RELOC_AGAINST_DISCARDED_SECTION (info, input_bfd, input_section,
					 rel, 1, relend, howto, 0, contents);

      if (info->relocatable)
	continue;

      switch (r_type)
	{
	case R_390_GOTPLT12:
	case R_390_GOTPLT16:
	case R_390_GOTPLT20:
	case R_390_GOTPLT32:
	case R_390_GOTPLT64:
	case R_390_GOTPLTENT:
	  /* There are three cases for a GOTPLT relocation. 1) The
	     relocation is against the jump slot entry of a plt that
	     will get emitted to the output file. 2) The relocation
	     is against the jump slot of a plt entry that has been
	     removed. cgc_s390_adjust_gotplt has created a GOT entry
	     as replacement. 3) The relocation is against a local symbol.
	     Cases 2) and 3) are the same as the GOT relocation code
	     so we just have to test for case 1 and fall through for
	     the other two.  */
	  if (h != NULL && h->plt.offset != (bfd_vma) -1)
	    {
	      bfd_vma plt_index;

	      if (s390_is_ifunc_symbol_p (h))
		{
		  plt_index = h->plt.offset / PLT_ENTRY_SIZE;
		  relocation = (plt_index * GOT_ENTRY_SIZE +
				htab->cgc.igotplt->output_offset);
		  if (r_type == R_390_GOTPLTENT)
		    relocation += htab->cgc.igotplt->output_section->vma;
		}
	      else
		{
		  /* Calc. index no.
		     Current offset - size first entry / entry size.  */
		  plt_index = (h->plt.offset - PLT_FIRST_ENTRY_SIZE) /
		    PLT_ENTRY_SIZE;

		  /* Offset in GOT is PLT index plus GOT headers(3)
		     times 4, addr & GOT addr.  */
		  relocation = (plt_index + 3) * GOT_ENTRY_SIZE;
		  if (r_type == R_390_GOTPLTENT)
		    relocation += htab->cgc.sgot->output_section->vma;
		}
	      unresolved_reloc = FALSE;
	      break;
	    }
	  /* Fall through.  */

	case R_390_GOT12:
	case R_390_GOT16:
	case R_390_GOT20:
	case R_390_GOT32:
	case R_390_GOT64:
	case R_390_GOTENT:
	  /* Relocation is to the entry for this symbol in the global
	     offset table.  */
	  if (base_got == NULL)
	    abort ();

	  if (h != NULL)
	    {
	      bfd_boolean dyn;

	      off = h->got.offset;
	      dyn = htab->cgc.dynamic_sections_created;

	      if (s390_is_ifunc_symbol_p (h))
		{
		  BFD_ASSERT (h->plt.offset != (bfd_vma) -1);
		  if (off == (bfd_vma)-1)
		    {
		      /* No explicit GOT usage so redirect to the
			 got.iplt slot.  */
		      base_got = htab->cgc.igotplt;
		      off = h->plt.offset / PLT_ENTRY_SIZE * GOT_ENTRY_SIZE;
		    }
		  else
		    {
		      /* Explicit GOT slots must contain the address
			 of the PLT slot. This will be handled in
			 finish_dynamic_symbol.  */
		    }
		}
	      else if (! WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, info->shared, h)
		       || (info->shared
			   && SYMBOL_REFERENCES_LOCAL (info, h))
		       || (CGC_ST_VISIBILITY (h->other)
			   && h->root.type == bfd_link_hash_undefweak))
		{
		  /* This is actually a static link, or it is a
		     -Bsymbolic link and the symbol is defined
		     locally, or the symbol was forced to be local
		     because of a version file.  We must initialize
		     this entry in the global offset table.  Since the
		     offset must always be a multiple of 2, we use the
		     least significant bit to record whether we have
		     initialized it already.

		     When doing a dynamic link, we create a .rel.got
		     relocation entry to initialize the value.  This
		     is done in the finish_dynamic_symbol routine.  */
		  if ((off & 1) != 0)
		    off &= ~1;
		  else
		    {
		      bfd_put_64 (output_bfd, relocation,
				  base_got->contents + off);
		      h->got.offset |= 1;
		    }

		  if ((h->def_regular
		       && info->shared
		       && SYMBOL_REFERENCES_LOCAL (info, h))
		      /* lgrl rx,sym@GOTENT -> larl rx, sym */
		      && ((r_type == R_390_GOTENT
			   && (bfd_get_16 (input_bfd,
					   contents + rel->r_offset - 2)
			       & 0xff0f) == 0xc408)
			  /* lg rx, sym@GOT(r12) -> larl rx, sym */
			  || (r_type == R_390_GOT20
			      && (bfd_get_32 (input_bfd,
					      contents + rel->r_offset - 2)
				  & 0xff00f000) == 0xe300c000
			      && bfd_get_8 (input_bfd,
					    contents + rel->r_offset + 3) == 0x04)))

		    {
		      unsigned short new_insn =
			(0xc000 | (bfd_get_8 (input_bfd,
					      contents + rel->r_offset - 1) & 0xf0));
		      bfd_put_16 (output_bfd, new_insn,
				  contents + rel->r_offset - 2);
		      r_type = R_390_PC32DBL;
		      rel->r_addend = 2;
		      howto = cgc_howto_table + r_type;
		      relocation = h->root.u.def.value
			+ h->root.u.def.section->output_section->vma
			+ h->root.u.def.section->output_offset;
		      goto do_relocation;
		    }
		}
	      else
		unresolved_reloc = FALSE;
	    }
	  else
	    {
	      if (local_got_offsets == NULL)
		abort ();

	      off = local_got_offsets[r_symndx];

	      /* The offset must always be a multiple of 8.  We use
		 the least significant bit to record whether we have
		 already generated the necessary reloc.  */
	      if ((off & 1) != 0)
		off &= ~1;
	      else
		{
		  bfd_put_64 (output_bfd, relocation,
			      htab->cgc.sgot->contents + off);

		  if (info->shared)
		    {
		      asection *s;
		      Cgc_Internal_Rela outrel;
		      bfd_byte *loc;

		      s = htab->cgc.srelgot;
		      if (s == NULL)
			abort ();

		      outrel.r_offset = (htab->cgc.sgot->output_section->vma
					 + htab->cgc.sgot->output_offset
					 + off);
		      outrel.r_info = CGC64_R_INFO (0, R_390_RELATIVE);
		      outrel.r_addend = relocation;
		      loc = s->contents;
		      loc += s->reloc_count++ * sizeof (Cgc64_External_Rela);
		      bfd_cgc64_swap_reloca_out (output_bfd, &outrel, loc);
		    }

		  local_got_offsets[r_symndx] |= 1;
		}
	    }

	  if (off >= (bfd_vma) -2)
	    abort ();

	  relocation = base_got->output_offset + off;

	  /* For @GOTENT the relocation is against the offset between
	     the instruction and the symbols entry in the GOT and not
	     between the start of the GOT and the symbols entry. We
	     add the vma of the GOT to get the correct value.  */
	  if (   r_type == R_390_GOTENT
	      || r_type == R_390_GOTPLTENT)
	    relocation += base_got->output_section->vma;

	  break;

	case R_390_GOTOFF16:
	case R_390_GOTOFF32:
	case R_390_GOTOFF64:
	  /* Relocation is relative to the start of the global offset
	     table.  */

	  /* Note that sgot->output_offset is not involved in this
	     calculation.  We always want the start of .got.  If we
	     defined _GLOBAL_OFFSET_TABLE in a different way, as is
	     permitted by the ABI, we might have to change this
	     calculation.  */
	  relocation -= htab->cgc.sgot->output_section->vma;
	  break;

	case R_390_GOTPC:
	case R_390_GOTPCDBL:
	  /* Use global offset table as symbol value.  */
	  relocation = htab->cgc.sgot->output_section->vma;
	  unresolved_reloc = FALSE;
	  break;

	case R_390_PLT12DBL:
	case R_390_PLT16DBL:
	case R_390_PLT24DBL:
	case R_390_PLT32:
	case R_390_PLT32DBL:
	case R_390_PLT64:
	  /* Relocation is to the entry for this symbol in the
	     procedure linkage table.  */

	  /* Resolve a PLT32 reloc against a local symbol directly,
	     without using the procedure linkage table.  */
	  if (h == NULL)
	    break;

	  if (h->plt.offset == (bfd_vma) -1
	      || (htab->cgc.splt == NULL && !s390_is_ifunc_symbol_p (h)))
	    {
	      /* We didn't make a PLT entry for this symbol.  This
		 happens when statically linking PIC code, or when
		 using -Bsymbolic.  */
	      break;
	    }
	  if (s390_is_ifunc_symbol_p (h))
	    relocation = (htab->cgc.iplt->output_section->vma
			  + htab->cgc.iplt->output_offset
			  + h->plt.offset);
	  else
	    relocation = (htab->cgc.splt->output_section->vma
			  + htab->cgc.splt->output_offset
			  + h->plt.offset);
	  unresolved_reloc = FALSE;
	  break;

	case R_390_PLTOFF16:
	case R_390_PLTOFF32:
	case R_390_PLTOFF64:
	  /* Relocation is to the entry for this symbol in the
	     procedure linkage table relative to the start of the GOT.  */

	  /* For local symbols or if we didn't make a PLT entry for
	     this symbol resolve the symbol directly.  */
	  if (h == NULL
	      || h->plt.offset == (bfd_vma) -1
	      || (htab->cgc.splt == NULL && !s390_is_ifunc_symbol_p (h)))
	    {
	      relocation -= htab->cgc.sgot->output_section->vma;
	      break;
	    }

	  if (s390_is_ifunc_symbol_p (h))
	    relocation = (htab->cgc.iplt->output_section->vma
			  + htab->cgc.iplt->output_offset
			  + h->plt.offset
			  - htab->cgc.sgot->output_section->vma);
	  else
	    relocation = (htab->cgc.splt->output_section->vma
			  + htab->cgc.splt->output_offset
			  + h->plt.offset
			  - htab->cgc.sgot->output_section->vma);
	  unresolved_reloc = FALSE;
	  break;

	case R_390_8:
	case R_390_16:
	case R_390_32:
	case R_390_64:
	case R_390_PC16:
	case R_390_PC12DBL:
	case R_390_PC16DBL:
	case R_390_PC24DBL:
	case R_390_PC32:
	case R_390_PC32DBL:
	case R_390_PC64:

	  if (h != NULL
	      && s390_is_ifunc_symbol_p (h)
	      && h->def_regular)
	    {
	      if (!info->shared || !h->non_got_ref)
		{
		  /* For a non-shared object STT_GNU_IFUNC symbol must
		     go through PLT.  */
		  relocation = (htab->cgc.iplt->output_section->vma
				+ htab->cgc.iplt->output_offset
				+ h ->plt.offset);
		  goto do_relocation;
		}
	      else
		{
		  /* For shared objects a runtime relocation is needed.  */

		  Cgc_Internal_Rela outrel;
		  asection *sreloc;

		  /* Need a dynamic relocation to get the real function
		     address.  */
		  outrel.r_offset = _bfd_cgc_section_offset (output_bfd,
							     info,
							     input_section,
							     rel->r_offset);
		  if (outrel.r_offset == (bfd_vma) -1
		      || outrel.r_offset == (bfd_vma) -2)
		    abort ();

		  outrel.r_offset += (input_section->output_section->vma
				      + input_section->output_offset);

		  if (h->dynindx == -1
		      || h->forced_local
		      || info->executable)
		    {
		      /* This symbol is resolved locally.  */
		      outrel.r_info = CGC64_R_INFO (0, R_390_IRELATIVE);
		      outrel.r_addend = (h->root.u.def.value
					 + h->root.u.def.section->output_section->vma
					 + h->root.u.def.section->output_offset);
		    }
		  else
		    {
		      outrel.r_info = CGC64_R_INFO (h->dynindx, r_type);
		      outrel.r_addend = 0;
		    }

		  sreloc = htab->cgc.irelifunc;
		  cgc_append_rela (output_bfd, sreloc, &outrel);

		  /* If this reloc is against an external symbol, we
		     do not want to fiddle with the addend.  Otherwise,
		     we need to include the symbol value so that it
		     becomes an addend for the dynamic reloc.  For an
		     internal symbol, we have updated addend.  */
		  continue;
		}
	    }

	  if ((input_section->flags & SEC_ALLOC) == 0)
	    break;

	  if ((info->shared
	       && (h == NULL
		   || CGC_ST_VISIBILITY (h->other) == STV_DEFAULT
		   || h->root.type != bfd_link_hash_undefweak)
	       && ((r_type != R_390_PC16
		    && r_type != R_390_PC12DBL
		    && r_type != R_390_PC16DBL
		    && r_type != R_390_PC24DBL
		    && r_type != R_390_PC32
		    && r_type != R_390_PC32DBL
		    && r_type != R_390_PC64)
		   || !SYMBOL_CALLS_LOCAL (info, h)))
	      || (ELIMINATE_COPY_RELOCS
		  && !info->shared
		  && h != NULL
		  && h->dynindx != -1
		  && !h->non_got_ref
		  && ((h->def_dynamic
		       && !h->def_regular)
		      || h->root.type == bfd_link_hash_undefweak
		      || h->root.type == bfd_link_hash_undefined)))
	    {
	      Cgc_Internal_Rela outrel;
	      bfd_boolean skip, relocate;
	      asection *sreloc;
	      bfd_byte *loc;

	      /* When generating a shared object, these relocations
		 are copied into the output file to be resolved at run
		 time.  */
	      skip = FALSE;
	      relocate = FALSE;

	      outrel.r_offset =
		_bfd_cgc_section_offset (output_bfd, info, input_section,
					 rel->r_offset);
	      if (outrel.r_offset == (bfd_vma) -1)
		skip = TRUE;
	      else if (outrel.r_offset == (bfd_vma) -2)
		skip = TRUE, relocate = TRUE;

	      outrel.r_offset += (input_section->output_section->vma
				  + input_section->output_offset);

	      if (skip)
		memset (&outrel, 0, sizeof outrel);
	      else if (h != NULL
		       && h->dynindx != -1
		       && (r_type == R_390_PC16
			   || r_type == R_390_PC12DBL
			   || r_type == R_390_PC16DBL
			   || r_type == R_390_PC24DBL
			   || r_type == R_390_PC32
			   || r_type == R_390_PC32DBL
			   || r_type == R_390_PC64
			   || !info->shared
			   || !SYMBOLIC_BIND (info, h)
			   || !h->def_regular))
		{
		  outrel.r_info = CGC64_R_INFO (h->dynindx, r_type);
		  outrel.r_addend = rel->r_addend;
		}
	      else
		{
		  /* This symbol is local, or marked to become local.  */
		  outrel.r_addend = relocation + rel->r_addend;
		  if (r_type == R_390_64)
		    {
		      relocate = TRUE;
		      outrel.r_info = CGC64_R_INFO (0, R_390_RELATIVE);
		    }
		  else
		    {
		      long sindx;

		      if (bfd_is_abs_section (sec))
			sindx = 0;
		      else if (sec == NULL || sec->owner == NULL)
			{
			  bfd_set_error(bfd_error_bad_value);
			  return FALSE;
			}
		      else
			{
			  asection *osec;

			  osec = sec->output_section;
			  sindx = cgc_section_data (osec)->dynindx;

			  if (sindx == 0)
			    {
			      osec = htab->cgc.text_index_section;
			      sindx = cgc_section_data (osec)->dynindx;
			    }
			  BFD_ASSERT (sindx != 0);

			  /* We are turning this relocation into one
			     against a section symbol, so subtract out
			     the output section's address but not the
			     offset of the input section in the output
			     section.  */
			  outrel.r_addend -= osec->vma;
			}
		      outrel.r_info = CGC64_R_INFO (sindx, r_type);
		    }
		}

	      sreloc = cgc_section_data (input_section)->sreloc;
	      if (sreloc == NULL)
		abort ();

	      loc = sreloc->contents;
	      loc += sreloc->reloc_count++ * sizeof (Cgc64_External_Rela);
	      bfd_cgc64_swap_reloca_out (output_bfd, &outrel, loc);

	      /* If this reloc is against an external symbol, we do
		 not want to fiddle with the addend.  Otherwise, we
		 need to include the symbol value so that it becomes
		 an addend for the dynamic reloc.  */
	      if (! relocate)
		continue;
	    }

	  break;

	  /* Relocations for tls literal pool entries.  */
	case R_390_TLS_IE64:
	  if (info->shared)
	    {
	      Cgc_Internal_Rela outrel;
	      asection *sreloc;
	      bfd_byte *loc;

	      outrel.r_offset = rel->r_offset
				+ input_section->output_section->vma
				+ input_section->output_offset;
	      outrel.r_info = CGC64_R_INFO (0, R_390_RELATIVE);
	      sreloc = cgc_section_data (input_section)->sreloc;
	      if (sreloc == NULL)
		abort ();
	      loc = sreloc->contents;
	      loc += sreloc->reloc_count++ * sizeof (Cgc64_External_Rela);
	      bfd_cgc64_swap_reloc_out (output_bfd, &outrel, loc);
	    }
	  /* Fall through.  */

	case R_390_TLS_GD64:
	case R_390_TLS_GOTIE64:
	  r_type = cgc_s390_tls_transition (info, r_type, h == NULL);
	  tls_type = GOT_UNKNOWN;
	  if (h == NULL && local_got_offsets)
	    tls_type = cgc_s390_local_got_tls_type (input_bfd) [r_symndx];
	  else if (h != NULL)
	    {
	      tls_type = cgc_s390_hash_entry(h)->tls_type;
	      if (!info->shared && h->dynindx == -1 && tls_type >= GOT_TLS_IE)
		r_type = R_390_TLS_LE64;
	    }
	  if (r_type == R_390_TLS_GD64 && tls_type >= GOT_TLS_IE)
	    r_type = R_390_TLS_IE64;

	  if (r_type == R_390_TLS_LE64)
	    {
	      /* This relocation gets optimized away by the local exec
		 access optimization.  */
	      BFD_ASSERT (! unresolved_reloc);
	      bfd_put_64 (output_bfd, -tpoff (info, relocation),
			  contents + rel->r_offset);
	      continue;
	    }

	  if (htab->cgc.sgot == NULL)
	    abort ();

	  if (h != NULL)
	    off = h->got.offset;
	  else
	    {
	      if (local_got_offsets == NULL)
		abort ();

	      off = local_got_offsets[r_symndx];
	    }

	emit_tls_relocs:

	  if ((off & 1) != 0)
	    off &= ~1;
	  else
	    {
	      Cgc_Internal_Rela outrel;
	      bfd_byte *loc;
	      int dr_type, indx;

	      if (htab->cgc.srelgot == NULL)
		abort ();

	      outrel.r_offset = (htab->cgc.sgot->output_section->vma
				 + htab->cgc.sgot->output_offset + off);

	      indx = h && h->dynindx != -1 ? h->dynindx : 0;
	      if (r_type == R_390_TLS_GD64)
		dr_type = R_390_TLS_DTPMOD;
	      else
		dr_type = R_390_TLS_TPOFF;
	      if (dr_type == R_390_TLS_TPOFF && indx == 0)
		outrel.r_addend = relocation - dtpoff_base (info);
	      else
		outrel.r_addend = 0;
	      outrel.r_info = CGC64_R_INFO (indx, dr_type);
	      loc = htab->cgc.srelgot->contents;
	      loc += htab->cgc.srelgot->reloc_count++
		* sizeof (Cgc64_External_Rela);
	      bfd_cgc64_swap_reloca_out (output_bfd, &outrel, loc);

	      if (r_type == R_390_TLS_GD64)
		{
		  if (indx == 0)
		    {
	    	      BFD_ASSERT (! unresolved_reloc);
		      bfd_put_64 (output_bfd,
				  relocation - dtpoff_base (info),
				  htab->cgc.sgot->contents + off + GOT_ENTRY_SIZE);
		    }
		  else
		    {
		      outrel.r_info = CGC64_R_INFO (indx, R_390_TLS_DTPOFF);
		      outrel.r_offset += GOT_ENTRY_SIZE;
		      outrel.r_addend = 0;
		      htab->cgc.srelgot->reloc_count++;
		      loc += sizeof (Cgc64_External_Rela);
		      bfd_cgc64_swap_reloca_out (output_bfd, &outrel, loc);
		    }
		}

	      if (h != NULL)
		h->got.offset |= 1;
	      else
		local_got_offsets[r_symndx] |= 1;
	    }

	  if (off >= (bfd_vma) -2)
	    abort ();
	  if (r_type == CGC64_R_TYPE (rel->r_info))
	    {
	      relocation = htab->cgc.sgot->output_offset + off;
	      if (r_type == R_390_TLS_IE64 || r_type == R_390_TLS_IEENT)
		relocation += htab->cgc.sgot->output_section->vma;
	      unresolved_reloc = FALSE;
	    }
	  else
	    {
	      bfd_put_64 (output_bfd, htab->cgc.sgot->output_offset + off,
			  contents + rel->r_offset);
	      continue;
	    }
	  break;

	case R_390_TLS_GOTIE12:
	case R_390_TLS_GOTIE20:
	case R_390_TLS_IEENT:
	  if (h == NULL)
	    {
	      if (local_got_offsets == NULL)
		abort();
	      off = local_got_offsets[r_symndx];
	      if (info->shared)
		goto emit_tls_relocs;
	    }
	  else
	    {
	      off = h->got.offset;
	      tls_type = cgc_s390_hash_entry(h)->tls_type;
	      if (info->shared || h->dynindx != -1 || tls_type < GOT_TLS_IE)
		goto emit_tls_relocs;
	    }

	  if (htab->cgc.sgot == NULL)
	    abort ();

	  BFD_ASSERT (! unresolved_reloc);
	  bfd_put_64 (output_bfd, -tpoff (info, relocation),
		      htab->cgc.sgot->contents + off);
	  relocation = htab->cgc.sgot->output_offset + off;
	  if (r_type == R_390_TLS_IEENT)
	    relocation += htab->cgc.sgot->output_section->vma;
	  unresolved_reloc = FALSE;
	  break;

	case R_390_TLS_LDM64:
	  if (! info->shared)
	    /* The literal pool entry this relocation refers to gets ignored
	       by the optimized code of the local exec model. Do nothing
	       and the value will turn out zero.  */
	    continue;

	  if (htab->cgc.sgot == NULL)
	    abort ();

	  off = htab->tls_ldm_got.offset;
	  if (off & 1)
	    off &= ~1;
	  else
	    {
	      Cgc_Internal_Rela outrel;
	      bfd_byte *loc;

	      if (htab->cgc.srelgot == NULL)
		abort ();

	      outrel.r_offset = (htab->cgc.sgot->output_section->vma
				 + htab->cgc.sgot->output_offset + off);

	      bfd_put_64 (output_bfd, 0,
			  htab->cgc.sgot->contents + off + GOT_ENTRY_SIZE);
	      outrel.r_info = CGC64_R_INFO (0, R_390_TLS_DTPMOD);
	      outrel.r_addend = 0;
	      loc = htab->cgc.srelgot->contents;
	      loc += htab->cgc.srelgot->reloc_count++
		* sizeof (Cgc64_External_Rela);
	      bfd_cgc64_swap_reloca_out (output_bfd, &outrel, loc);
	      htab->tls_ldm_got.offset |= 1;
	    }
	  relocation = htab->cgc.sgot->output_offset + off;
	  unresolved_reloc = FALSE;
	  break;

	case R_390_TLS_LE64:
	  if (info->shared)
	    {
	      /* Linking a shared library with non-fpic code requires
		 a R_390_TLS_TPOFF relocation.  */
	      Cgc_Internal_Rela outrel;
	      asection *sreloc;
	      bfd_byte *loc;
	      int indx;

	      outrel.r_offset = rel->r_offset
				+ input_section->output_section->vma
				+ input_section->output_offset;
	      if (h != NULL && h->dynindx != -1)
		indx = h->dynindx;
	      else
		indx = 0;
	      outrel.r_info = CGC64_R_INFO (indx, R_390_TLS_TPOFF);
	      if (indx == 0)
		outrel.r_addend = relocation - dtpoff_base (info);
	      else
		outrel.r_addend = 0;
	      sreloc = cgc_section_data (input_section)->sreloc;
	      if (sreloc == NULL)
		abort ();
	      loc = sreloc->contents;
	      loc += sreloc->reloc_count++ * sizeof (Cgc64_External_Rela);
	      bfd_cgc64_swap_reloca_out (output_bfd, &outrel, loc);
	    }
	  else
	    {
	      BFD_ASSERT (! unresolved_reloc);
	      bfd_put_64 (output_bfd, -tpoff (info, relocation),
			  contents + rel->r_offset);
	    }
	  continue;

	case R_390_TLS_LDO64:
	  if (info->shared || (input_section->flags & SEC_DEBUGGING))
	    relocation -= dtpoff_base (info);
	  else
	    /* When converting LDO to LE, we must negate.  */
	    relocation = -tpoff (info, relocation);
	  break;

	  /* Relocations for tls instructions.  */
	case R_390_TLS_LOAD:
	case R_390_TLS_GDCALL:
	case R_390_TLS_LDCALL:
	  tls_type = GOT_UNKNOWN;
	  if (h == NULL && local_got_offsets)
	    tls_type = cgc_s390_local_got_tls_type (input_bfd) [r_symndx];
	  else if (h != NULL)
	    tls_type = cgc_s390_hash_entry(h)->tls_type;

	  if (tls_type == GOT_TLS_GD)
	    continue;

	  if (r_type == R_390_TLS_LOAD)
	    {
	      if (!info->shared && (h == NULL || h->dynindx == -1))
		{
		  /* IE->LE transition. Four valid cases:
		     lg %rx,(0,%ry)    -> sllg %rx,%ry,0
		     lg %rx,(%ry,0)    -> sllg %rx,%ry,0
		     lg %rx,(%ry,%r12) -> sllg %rx,%ry,0
		     lg %rx,(%r12,%ry) -> sllg %rx,%ry,0  */
		  unsigned int insn0, insn1, ry;

		  insn0 = bfd_get_32 (input_bfd, contents + rel->r_offset);
		  insn1 = bfd_get_16 (input_bfd, contents + rel->r_offset + 4);
		  if (insn1 != 0x0004)
		    invalid_tls_insn (input_bfd, input_section, rel);
		  ry = 0;
		  if ((insn0 & 0xff00f000) == 0xe3000000)
		    /* lg %rx,0(%ry,0) -> sllg %rx,%ry,0  */
		    ry = (insn0 & 0x000f0000);
		  else if ((insn0 & 0xff0f0000) == 0xe3000000)
		    /* lg %rx,0(0,%ry) -> sllg %rx,%ry,0  */
		    ry = (insn0 & 0x0000f000) << 4;
		  else if ((insn0 & 0xff00f000) == 0xe300c000)
		    /* lg %rx,0(%ry,%r12) -> sllg %rx,%ry,0  */
		    ry = (insn0 & 0x000f0000);
		  else if ((insn0 & 0xff0f0000) == 0xe30c0000)
		    /* lg %rx,0(%r12,%ry) -> sllg %rx,%ry,0  */
		    ry = (insn0 & 0x0000f000) << 4;
		  else
		    invalid_tls_insn (input_bfd, input_section, rel);
		  insn0 = 0xeb000000 | (insn0 & 0x00f00000) | ry;
		  insn1 = 0x000d;
		  bfd_put_32 (output_bfd, insn0, contents + rel->r_offset);
		  bfd_put_16 (output_bfd, insn1, contents + rel->r_offset + 4);
		}
	    }
	  else if (r_type == R_390_TLS_GDCALL)
	    {
	      unsigned int insn0, insn1;

	      insn0 = bfd_get_32 (input_bfd, contents + rel->r_offset);
	      insn1 = bfd_get_16 (input_bfd, contents + rel->r_offset + 4);
	      if ((insn0 & 0xffff0000) != 0xc0e50000)
		invalid_tls_insn (input_bfd, input_section, rel);
	      if (!info->shared && (h == NULL || h->dynindx == -1))
		{
		  /* GD->LE transition.
		     brasl %r14,__tls_get_addr@plt -> brcl 0,. */
		  insn0 = 0xc0040000;
		  insn1 = 0x0000;
		}
	      else
		{
		  /* GD->IE transition.
		     brasl %r14,__tls_get_addr@plt -> lg %r2,0(%r2,%r12)  */
		  insn0 = 0xe322c000;
		  insn1 = 0x0004;
		}
	      bfd_put_32 (output_bfd, insn0, contents + rel->r_offset);
	      bfd_put_16 (output_bfd, insn1, contents + rel->r_offset + 4);
	    }
	  else if (r_type == R_390_TLS_LDCALL)
	    {
	      if (!info->shared)
		{
		  unsigned int insn0, insn1;

		  insn0 = bfd_get_32 (input_bfd, contents + rel->r_offset);
		  insn1 = bfd_get_16 (input_bfd, contents + rel->r_offset + 4);
		  if ((insn0 & 0xffff0000) != 0xc0e50000)
		    invalid_tls_insn (input_bfd, input_section, rel);
		  /* LD->LE transition.
		     brasl %r14,__tls_get_addr@plt -> brcl 0,. */
		  insn0 = 0xc0040000;
		  insn1 = 0x0000;
		  bfd_put_32 (output_bfd, insn0, contents + rel->r_offset);
		  bfd_put_16 (output_bfd, insn1, contents + rel->r_offset + 4);
		}
	    }
	  continue;

	default:
	  break;
	}

      /* Dynamic relocs are not propagated for SEC_DEBUGGING sections
	 because such sections are not SEC_ALLOC and thus ld.so will
	 not process them.  */
      if (unresolved_reloc
	  && !((input_section->flags & SEC_DEBUGGING) != 0
	       && h->def_dynamic)
	  && _bfd_cgc_section_offset (output_bfd, info, input_section,
				      rel->r_offset) != (bfd_vma) -1)
	(*_bfd_error_handler)
	  (_("%B(%A+0x%lx): unresolvable %s relocation against symbol `%s'"),
	   input_bfd,
	   input_section,
	   (long) rel->r_offset,
	   howto->name,
	   h->root.root.string);

    do_relocation:

      /* When applying a 24 bit reloc we need to start one byte
	 earlier.  Otherwise the 32 bit get/put bfd operations might
	 access a byte after the actual section.  */
      if (r_type == R_390_PC24DBL
	  || r_type == R_390_PLT24DBL)
	rel->r_offset--;

      if (r_type == R_390_20
	  || r_type == R_390_GOT20
	  || r_type == R_390_GOTPLT20
	  || r_type == R_390_TLS_GOTIE20)
	{
	  relocation += rel->r_addend;
	  relocation = (relocation&0xfff) << 8 | (relocation&0xff000) >> 12;
	  r = _bfd_final_link_relocate (howto, input_bfd, input_section,
					contents, rel->r_offset,
					relocation, 0);
	}
      else
	r = _bfd_final_link_relocate (howto, input_bfd, input_section,
				      contents, rel->r_offset,
				      relocation, rel->r_addend);

      if (r != bfd_reloc_ok)
	{
	  const char *name;

	  if (h != NULL)
	    name = h->root.root.string;
	  else
	    {
	      name = bfd_cgc_string_from_cgc_section (input_bfd,
						      symtab_hdr->sh_link,
						      sym->st_name);
	      if (name == NULL)
		return FALSE;
	      if (*name == '\0')
		name = bfd_section_name (input_bfd, sec);
	    }

	  if (r == bfd_reloc_overflow)
	    {

	      if (! ((*info->callbacks->reloc_overflow)
		     (info, (h ? &h->root : NULL), name, howto->name,
		      (bfd_vma) 0, input_bfd, input_section,
		      rel->r_offset)))
		return FALSE;
	    }
	  else
	    {
	      (*_bfd_error_handler)
		(_("%B(%A+0x%lx): reloc against `%s': error %d"),
		 input_bfd, input_section,
		 (long) rel->r_offset, name, (int) r);
	      return FALSE;
	    }
	}
    }

  return TRUE;
}

/* Generate the PLT slots together with the dynamic relocations needed
   for IFUNC symbols.  */

static void
cgc_s390_finish_ifunc_symbol (bfd *output_bfd,
			      struct bfd_link_info *info,
			      struct cgc_link_hash_entry *h,
			      struct cgc_s390_link_hash_table *htab,
			      bfd_vma plt_offset,
			      bfd_vma resolver_address)
{
  bfd_vma plt_index;
  bfd_vma got_offset;
  Cgc_Internal_Rela rela;
  bfd_byte *loc;
  asection *plt, *gotplt, *relplt;

  if (htab->cgc.iplt == NULL
      || htab->cgc.igotplt == NULL
      || htab->cgc.irelplt == NULL)
    abort ();

  /* Index of the PLT slot within iplt section.  */
  plt_index = plt_offset / PLT_ENTRY_SIZE;
  plt = htab->cgc.iplt;
  /* Offset into the igot.plt section.  */
  got_offset = plt_index * GOT_ENTRY_SIZE;
  gotplt = htab->cgc.igotplt;
  relplt = htab->cgc.irelplt;

  /* Fill in the blueprint of a PLT.  */
  memcpy (plt->contents + plt_offset, cgc_s390x_plt_entry,
	  PLT_ENTRY_SIZE);

  /* Fixup the relative address to the GOT entry */
  bfd_put_32 (output_bfd,
	      (gotplt->output_section->vma +
	       gotplt->output_offset + got_offset
	       - (plt->output_section->vma +
		  plt->output_offset +
		  plt_offset))/2,
	      plt->contents + plt_offset + 2);
  /* Fixup the relative branch to PLT 0 */
  bfd_put_32 (output_bfd, - (plt->output_offset +
			     (PLT_ENTRY_SIZE * plt_index) + 22)/2,
	      plt->contents + plt_offset + 24);
  /* Fixup offset into .rela.plt section.  */
  bfd_put_32 (output_bfd, relplt->output_offset +
	      plt_index * sizeof (Cgc64_External_Rela),
	      plt->contents + plt_offset + 28);

  /* Fill in the entry in the global offset table.
     Points to instruction after GOT offset.  */
  bfd_put_64 (output_bfd,
	      (plt->output_section->vma
	       + plt->output_offset
	       + plt_offset
	       + 14),
	      gotplt->contents + got_offset);

  /* Fill in the entry in the .rela.plt section.  */
  rela.r_offset = (gotplt->output_section->vma
		   + gotplt->output_offset
		   + got_offset);

  if (!h
      || h->dynindx == -1
      || ((info->executable
	   || CGC_ST_VISIBILITY (h->other) != STV_DEFAULT)
	  && h->def_regular))
    {
      /* The symbol can be locally resolved.  */
      rela.r_info = CGC64_R_INFO (0, R_390_IRELATIVE);
      rela.r_addend = resolver_address;
    }
  else
    {
      rela.r_info = CGC64_R_INFO (h->dynindx, R_390_JMP_SLOT);
      rela.r_addend = 0;
    }

  loc = relplt->contents + plt_index * sizeof (Cgc64_External_Rela);
  bfd_cgc64_swap_reloca_out (output_bfd, &rela, loc);
}


/* Finish up dynamic symbol handling.  We set the contents of various
   dynamic sections here.  */

static bfd_boolean
cgc_s390_finish_dynamic_symbol (bfd *output_bfd,
				struct bfd_link_info *info,
				struct cgc_link_hash_entry *h,
				Cgc_Internal_Sym *sym)
{
  struct cgc_s390_link_hash_table *htab;
  struct cgc_s390_link_hash_entry *eh = (struct cgc_s390_link_hash_entry*)h;

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  if (h->plt.offset != (bfd_vma) -1)
    {
      bfd_vma plt_index;
      bfd_vma got_offset;
      Cgc_Internal_Rela rela;
      bfd_byte *loc;

      /* This symbol has an entry in the procedure linkage table.  Set
	 it up.  */
      if (s390_is_ifunc_symbol_p (h))
	{
	  /* If we can resolve the IFUNC symbol locally we generate an
	     IRELATIVE reloc.  */
	  cgc_s390_finish_ifunc_symbol (output_bfd, info, h, htab, h->plt.offset,
					eh->ifunc_resolver_address +
					eh->ifunc_resolver_section->output_offset +
					eh->ifunc_resolver_section->output_section->vma);
				 ;
	  /* Fallthrough.  Handling of explicit GOT slots of IFUNC
	     symbols is below.  */
	}
      else
	{
	  if (h->dynindx == -1
	      || htab->cgc.splt == NULL
	      || htab->cgc.sgotplt == NULL
	      || htab->cgc.srelplt == NULL)
	    abort ();

	  /* Calc. index no.
	     Current offset - size first entry / entry size.  */
	  plt_index = (h->plt.offset - PLT_FIRST_ENTRY_SIZE) / PLT_ENTRY_SIZE;

	  /* Offset in GOT is PLT index plus GOT headers(3) times 8,
	     addr & GOT addr.  */
	  got_offset = (plt_index + 3) * GOT_ENTRY_SIZE;

	  /* Fill in the blueprint of a PLT.  */
	  memcpy (htab->cgc.splt->contents + h->plt.offset, cgc_s390x_plt_entry,
		  PLT_ENTRY_SIZE);

	  /* Fixup the relative address to the GOT entry */
	  bfd_put_32 (output_bfd,
		      (htab->cgc.sgotplt->output_section->vma +
		       htab->cgc.sgotplt->output_offset + got_offset
		       - (htab->cgc.splt->output_section->vma +
			  htab->cgc.splt->output_offset +
			  h->plt.offset))/2,
		      htab->cgc.splt->contents + h->plt.offset + 2);
	  /* Fixup the relative branch to PLT 0 */
	  bfd_put_32 (output_bfd, - (PLT_FIRST_ENTRY_SIZE +
				     (PLT_ENTRY_SIZE * plt_index) + 22)/2,
		      htab->cgc.splt->contents + h->plt.offset + 24);
	  /* Fixup offset into .rela.plt section.  */
	  bfd_put_32 (output_bfd, plt_index * sizeof (Cgc64_External_Rela),
		      htab->cgc.splt->contents + h->plt.offset + 28);

	  /* Fill in the entry in the global offset table.
	     Points to instruction after GOT offset.  */
	  bfd_put_64 (output_bfd,
		      (htab->cgc.splt->output_section->vma
		       + htab->cgc.splt->output_offset
		       + h->plt.offset
		       + 14),
		      htab->cgc.sgotplt->contents + got_offset);

	  /* Fill in the entry in the .rela.plt section.  */
	  rela.r_offset = (htab->cgc.sgotplt->output_section->vma
			   + htab->cgc.sgotplt->output_offset
			   + got_offset);
	  rela.r_info = CGC64_R_INFO (h->dynindx, R_390_JMP_SLOT);
	  rela.r_addend = 0;
	  loc = htab->cgc.srelplt->contents + plt_index *
	    sizeof (Cgc64_External_Rela);
	  bfd_cgc64_swap_reloca_out (output_bfd, &rela, loc);

	  if (!h->def_regular)
	    {
	      /* Mark the symbol as undefined, rather than as defined in
		 the .plt section.  Leave the value alone.  This is a clue
		 for the dynamic linker, to make function pointer
		 comparisons work between an application and shared
		 library.  */
	      sym->st_shndx = SHN_UNDEF;
	    }
	}
    }

  if (h->got.offset != (bfd_vma) -1
      && cgc_s390_hash_entry(h)->tls_type != GOT_TLS_GD
      && cgc_s390_hash_entry(h)->tls_type != GOT_TLS_IE
      && cgc_s390_hash_entry(h)->tls_type != GOT_TLS_IE_NLT)
    {
      Cgc_Internal_Rela rela;
      bfd_byte *loc;

      /* This symbol has an entry in the global offset table.  Set it
	 up.  */
      if (htab->cgc.sgot == NULL || htab->cgc.srelgot == NULL)
	abort ();

      rela.r_offset = (htab->cgc.sgot->output_section->vma
		       + htab->cgc.sgot->output_offset
		       + (h->got.offset &~ (bfd_vma) 1));

      if (h->def_regular && s390_is_ifunc_symbol_p (h))
	{
	  if (info->shared)
	    {
	      /* An explicit GOT slot usage needs GLOB_DAT.  If the
		 symbol references local the implicit got.iplt slot
		 will be used and the IRELATIVE reloc has been created
		 above.  */
	      goto do_glob_dat;
	    }
	  else
	    {
	      /* For non-shared objects explicit GOT slots must be
		 filled with the PLT slot address for pointer
		 equality reasons.  */
	      bfd_put_64 (output_bfd, (htab->cgc.iplt->output_section->vma
				       + htab->cgc.iplt->output_offset
				       + h->plt.offset),
			  htab->cgc.sgot->contents + h->got.offset);
	      return TRUE;
	    }
	}
      else if (info->shared
	  && SYMBOL_REFERENCES_LOCAL (info, h))
	{
	  /* If this is a static link, or it is a -Bsymbolic link and
	     the symbol is defined locally or was forced to be local
	     because of a version file, we just want to emit a
	     RELATIVE reloc.  The entry in the global offset table
	     will already have been initialized in the
	     relocate_section function.  */
	  if (!h->def_regular)
	    return FALSE;
	  BFD_ASSERT((h->got.offset & 1) != 0);
	  rela.r_info = CGC64_R_INFO (0, R_390_RELATIVE);
	  rela.r_addend = (h->root.u.def.value
			   + h->root.u.def.section->output_section->vma
			   + h->root.u.def.section->output_offset);
	}
      else
	{
	  BFD_ASSERT((h->got.offset & 1) == 0);
do_glob_dat:
	  bfd_put_64 (output_bfd, (bfd_vma) 0, htab->cgc.sgot->contents + h->got.offset);
	  rela.r_info = CGC64_R_INFO (h->dynindx, R_390_GLOB_DAT);
	  rela.r_addend = 0;
	}

      loc = htab->cgc.srelgot->contents;
      loc += htab->cgc.srelgot->reloc_count++ * sizeof (Cgc64_External_Rela);
      bfd_cgc64_swap_reloca_out (output_bfd, &rela, loc);
    }

  if (h->needs_copy)
    {
      Cgc_Internal_Rela rela;
      bfd_byte *loc;

      /* This symbols needs a copy reloc.  Set it up.  */

      if (h->dynindx == -1
	  || (h->root.type != bfd_link_hash_defined
	      && h->root.type != bfd_link_hash_defweak)
	  || htab->srelbss == NULL)
	abort ();

      rela.r_offset = (h->root.u.def.value
		       + h->root.u.def.section->output_section->vma
		       + h->root.u.def.section->output_offset);
      rela.r_info = CGC64_R_INFO (h->dynindx, R_390_COPY);
      rela.r_addend = 0;
      loc = htab->srelbss->contents;
      loc += htab->srelbss->reloc_count++ * sizeof (Cgc64_External_Rela);
      bfd_cgc64_swap_reloca_out (output_bfd, &rela, loc);
    }

  /* Mark some specially defined symbols as absolute.  */
  if (h == htab->cgc.hdynamic
      || h == htab->cgc.hgot
      || h == htab->cgc.hplt)
    sym->st_shndx = SHN_ABS;

  return TRUE;
}

/* Used to decide how to sort relocs in an optimal manner for the
   dynamic linker, before writing them out.  */

static enum cgc_reloc_type_class
cgc_s390_reloc_type_class (const struct bfd_link_info *info ATTRIBUTE_UNUSED,
			   const asection *rel_sec ATTRIBUTE_UNUSED,
			   const Cgc_Internal_Rela *rela)
{
  switch ((int) CGC64_R_TYPE (rela->r_info))
    {
    case R_390_RELATIVE:
      return reloc_class_relative;
    case R_390_JMP_SLOT:
      return reloc_class_plt;
    case R_390_COPY:
      return reloc_class_copy;
    default:
      return reloc_class_normal;
    }
}

/* Finish up the dynamic sections.  */

static bfd_boolean
cgc_s390_finish_dynamic_sections (bfd *output_bfd,
				  struct bfd_link_info *info)
{
  struct cgc_s390_link_hash_table *htab;
  bfd *dynobj;
  asection *sdyn;
  bfd *ibfd;
  unsigned int i;

  htab = cgc_s390_hash_table (info);
  if (htab == NULL)
    return FALSE;

  dynobj = htab->cgc.dynobj;
  sdyn = bfd_get_linker_section (dynobj, ".dynamic");

  if (htab->cgc.dynamic_sections_created)
    {
      Cgc64_External_Dyn *dyncon, *dynconend;

      if (sdyn == NULL || htab->cgc.sgot == NULL)
	abort ();

      dyncon = (Cgc64_External_Dyn *) sdyn->contents;
      dynconend = (Cgc64_External_Dyn *) (sdyn->contents + sdyn->size);
      for (; dyncon < dynconend; dyncon++)
	{
	  Cgc_Internal_Dyn dyn;
	  asection *s;

	  bfd_cgc64_swap_dyn_in (dynobj, dyncon, &dyn);

	  switch (dyn.d_tag)
	    {
	    default:
	      continue;

	    case DT_PLTGOT:
	      dyn.d_un.d_ptr = htab->cgc.sgot->output_section->vma;
	      break;

	    case DT_JMPREL:
	      dyn.d_un.d_ptr = htab->cgc.srelplt->output_section->vma;
	      break;

	    case DT_PLTRELSZ:
	      s = htab->cgc.srelplt->output_section;
	      dyn.d_un.d_val = s->size;
	      break;

	    case DT_RELASZ:
	      /* The procedure linkage table relocs (DT_JMPREL) should
		 not be included in the overall relocs (DT_RELA).
		 Therefore, we override the DT_RELASZ entry here to
		 make it not include the JMPREL relocs.  Since the
		 linker script arranges for .rela.plt to follow all
		 other relocation sections, we don't have to worry
		 about changing the DT_RELA entry.  */
	      s = htab->cgc.srelplt->output_section;
	      dyn.d_un.d_val -= s->size;
	      break;
	    }

	  bfd_cgc64_swap_dyn_out (output_bfd, &dyn, dyncon);
	}

      /* Fill in the special first entry in the procedure linkage table.  */
      if (htab->cgc.splt && htab->cgc.splt->size > 0)
	{
	  /* fill in blueprint for plt 0 entry */
	  memcpy (htab->cgc.splt->contents, cgc_s390x_first_plt_entry,
		  PLT_FIRST_ENTRY_SIZE);
	  /* Fixup relative address to start of GOT */
	  bfd_put_32 (output_bfd,
		      (htab->cgc.sgotplt->output_section->vma +
		       htab->cgc.sgotplt->output_offset
		       - htab->cgc.splt->output_section->vma - 6)/2,
		      htab->cgc.splt->contents + 8);
	}
      if (cgc_section_data (htab->cgc.splt->output_section) != NULL)
	cgc_section_data (htab->cgc.splt->output_section)->this_hdr.sh_entsize
	  = PLT_ENTRY_SIZE;
    }

  if (htab->cgc.sgotplt)
    {
      /* Fill in the first three entries in the global offset table.  */
      if (htab->cgc.sgotplt->size > 0)
	{
	  bfd_put_64 (output_bfd,
		      (sdyn == NULL ? (bfd_vma) 0
		       : sdyn->output_section->vma + sdyn->output_offset),
		      htab->cgc.sgotplt->contents);
	  /* One entry for shared object struct ptr.  */
	  bfd_put_64 (output_bfd, (bfd_vma) 0, htab->cgc.sgotplt->contents + 8);
	  /* One entry for _dl_runtime_resolve.  */
	  bfd_put_64 (output_bfd, (bfd_vma) 0, htab->cgc.sgotplt->contents + 12);
	}

      cgc_section_data (htab->cgc.sgot->output_section)
	->this_hdr.sh_entsize = 8;
    }

  /* Finish dynamic symbol for local IFUNC symbols.  */
  for (ibfd = info->input_bfds; ibfd != NULL; ibfd = ibfd->link_next)
    {
      struct plt_entry *local_plt;
      Cgc_Internal_Sym *isym;
      Cgc_Internal_Shdr *symtab_hdr;

      symtab_hdr = &cgc_symtab_hdr (ibfd);

      local_plt = cgc_s390_local_plt (ibfd);
      if (local_plt != NULL)
	for (i = 0; i < symtab_hdr->sh_info; i++)
	  {
	    if (local_plt[i].plt.offset != (bfd_vma) -1)
	      {
		asection *sec = local_plt[i].sec;
		isym = bfd_sym_from_r_symndx (&htab->sym_cache, ibfd, i);
		if (isym == NULL)
		  return FALSE;

		if (CGC_ST_TYPE (isym->st_info) == STT_GNU_IFUNC)
		  cgc_s390_finish_ifunc_symbol (output_bfd, info, NULL, htab,
						local_plt[i].plt.offset,
						isym->st_value
						+ sec->output_section->vma
						+ sec->output_offset);

	      }
	  }
    }

  return TRUE;
}

/* Return address for Ith PLT stub in section PLT, for relocation REL
   or (bfd_vma) -1 if it should not be included.  */

static bfd_vma
cgc_s390_plt_sym_val (bfd_vma i, const asection *plt,
		      const arelent *rel ATTRIBUTE_UNUSED)
{
  return plt->vma + PLT_FIRST_ENTRY_SIZE + i * PLT_ENTRY_SIZE;
}

/* Why was the hash table entry size definition changed from
   ARCH_SIZE/8 to 4? This breaks the 64 bit dynamic linker and
   this is the only reason for the s390_cgc64_size_info structure.  */

const struct cgc_size_info s390_cgc64_size_info =
{
  sizeof (Cgc64_External_Ehdr),
  sizeof (Cgc64_External_Phdr),
  sizeof (Cgc64_External_Shdr),
  sizeof (Cgc64_External_Rel),
  sizeof (Cgc64_External_Rela),
  sizeof (Cgc64_External_Sym),
  sizeof (Cgc64_External_Dyn),
  sizeof (Cgc_External_Note),
  8,		/* hash-table entry size.  */
  1,		/* internal relocations per external relocations.  */
  64,		/* arch_size.  */
  3,		/* log_file_align.  */
  CGCCLASS64, EV_CURRENT,
  bfd_cgc64_write_out_phdrs,
  bfd_cgc64_write_shdrs_and_ehdr,
  bfd_cgc64_checksum_contents,
  bfd_cgc64_write_relocs,
  bfd_cgc64_swap_symbol_in,
  bfd_cgc64_swap_symbol_out,
  bfd_cgc64_slurp_reloc_table,
  bfd_cgc64_slurp_symbol_table,
  bfd_cgc64_swap_dyn_in,
  bfd_cgc64_swap_dyn_out,
  bfd_cgc64_swap_reloc_in,
  bfd_cgc64_swap_reloc_out,
  bfd_cgc64_swap_reloca_in,
  bfd_cgc64_swap_reloca_out
};

#define TARGET_BIG_SYM	bfd_cgc64_s390_vec
#define TARGET_BIG_NAME	"cgc64-s390"
#define CGC_ARCH	bfd_arch_s390
#define CGC_TARGET_ID	S390_CGC_DATA
#define CGC_MACHINE_CODE EM_S390
#define CGC_MACHINE_ALT1 EM_S390_OLD
#define CGC_MAXPAGESIZE 0x1000

#define cgc_backend_size_info		s390_cgc64_size_info

#define cgc_backend_can_gc_sections	1
#define cgc_backend_can_refcount	1
#define cgc_backend_want_got_plt	1
#define cgc_backend_plt_readonly	1
#define cgc_backend_want_plt_sym	0
#define cgc_backend_got_header_size	24
#define cgc_backend_rela_normal		1

#define cgc_info_to_howto		cgc_s390_info_to_howto

#define bfd_cgc64_bfd_is_local_label_name     cgc_s390_is_local_label_name
#define bfd_cgc64_bfd_link_hash_table_create  cgc_s390_link_hash_table_create
#define bfd_cgc64_bfd_reloc_type_lookup	      cgc_s390_reloc_type_lookup
#define bfd_cgc64_bfd_reloc_name_lookup cgc_s390_reloc_name_lookup

#define cgc_backend_adjust_dynamic_symbol     cgc_s390_adjust_dynamic_symbol
#define cgc_backend_check_relocs	      cgc_s390_check_relocs
#define cgc_backend_copy_indirect_symbol      cgc_s390_copy_indirect_symbol
#define cgc_backend_create_dynamic_sections   cgc_s390_create_dynamic_sections
#define cgc_backend_finish_dynamic_sections   cgc_s390_finish_dynamic_sections
#define cgc_backend_finish_dynamic_symbol     cgc_s390_finish_dynamic_symbol
#define cgc_backend_gc_mark_hook	      cgc_s390_gc_mark_hook
#define cgc_backend_gc_sweep_hook	      cgc_s390_gc_sweep_hook
#define cgc_backend_reloc_type_class	      cgc_s390_reloc_type_class
#define cgc_backend_relocate_section	      cgc_s390_relocate_section
#define cgc_backend_size_dynamic_sections     cgc_s390_size_dynamic_sections
#define cgc_backend_init_index_section	      _bfd_cgc_init_1_index_section
#define cgc_backend_plt_sym_val		      cgc_s390_plt_sym_val
#define cgc_backend_add_symbol_hook           cgc_s390_add_symbol_hook

#define bfd_cgc64_mkobject		cgc_s390_mkobject
#define cgc_backend_object_p		cgc_s390_object_p

/* Enable CGC64 archive functions.  */
#define bfd_cgc64_archive_functions
extern bfd_boolean bfd_cgc64_archive_slurp_armap (bfd *);
extern bfd_boolean bfd_cgc64_archive_write_armap (bfd *, unsigned int, struct orl *, unsigned int, int);

#define bfd_cgc64_archive_slurp_extended_name_table 	_bfd_archive_coff_slurp_extended_name_table
#define bfd_cgc64_archive_construct_extended_name_table _bfd_archive_coff_construct_extended_name_table
#define bfd_cgc64_archive_truncate_arname 		_bfd_archive_coff_truncate_arname
#define bfd_cgc64_archive_read_ar_hdr			_bfd_archive_coff_read_ar_hdr
#define bfd_cgc64_archive_write_ar_hdr			_bfd_archive_coff_write_ar_hdr
#define bfd_cgc64_archive_openr_next_archived_file 	_bfd_archive_coff_openr_next_archived_file
#define bfd_cgc64_archive_get_elt_at_index 		_bfd_archive_coff_get_elt_at_index
#define bfd_cgc64_archive_generic_stat_arch_elt 	_bfd_archive_coff_generic_stat_arch_elt
#define bfd_cgc64_archive_update_armap_timestamp 	_bfd_archive_coff_update_armap_timestamp

#include "cgc64-target.h"
