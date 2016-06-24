/* Generic support for 32-bit CGC
   Copyright 1993, 1995, 1998, 1999, 2001, 2002, 2004, 2005, 2007
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"
#include "cgc-bfd.h"

/* This does not include any relocation information, but should be
   good enough for GDB or objdump to read the file.  */

static reloc_howto_type dummy =
  HOWTO (0,			/* type */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 0,			/* bitsize */
	 FALSE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 NULL,			/* special_function */
	 "UNKNOWN",		/* name */
	 FALSE,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 FALSE);		/* pcrel_offset */

static void
cgc_generic_info_to_howto (bfd *abfd ATTRIBUTE_UNUSED,
			   arelent *bfd_reloc,
			   Cgc_Internal_Rela *cgc_reloc ATTRIBUTE_UNUSED)
{
  bfd_reloc->howto = &dummy;
}

static void
cgc_generic_info_to_howto_rel (bfd *abfd ATTRIBUTE_UNUSED,
			       arelent *bfd_reloc,
			       Cgc_Internal_Rela *cgc_reloc ATTRIBUTE_UNUSED)
{
  bfd_reloc->howto = &dummy;
}

static void
check_for_relocs (bfd * abfd, asection * o, void * failed)
{
  if ((o->flags & SEC_RELOC) != 0)
    {
      Cgc_Internal_Ehdr *ehdrp;

      ehdrp = cgc_cgcheader (abfd);
      _bfd_error_handler (_("%B: Relocations in generic CGC (EM: %d)"),
			  abfd, ehdrp->e_machine);

      bfd_set_error (bfd_error_wrong_format);
      * (bfd_boolean *) failed = TRUE;
    }
}

static bfd_boolean
cgc32_generic_link_add_symbols (bfd *abfd, struct bfd_link_info *info)
{
  bfd_boolean failed = FALSE;

  /* Check if there are any relocations.  */
  bfd_map_over_sections (abfd, check_for_relocs, & failed);

  if (failed)
    return FALSE;
  return bfd_cgc_link_add_symbols (abfd, info);
}

#define TARGET_LITTLE_SYM		bfd_cgc32_little_generic_vec
#define TARGET_LITTLE_NAME		"cgc32-little"
#define TARGET_BIG_SYM			bfd_cgc32_big_generic_vec
#define TARGET_BIG_NAME			"cgc32-big"
#define CGC_ARCH			bfd_arch_unknown
#define CGC_MACHINE_CODE		EM_NONE
#define CGC_MAXPAGESIZE			0x1
#define bfd_cgc32_bfd_reloc_type_lookup bfd_default_reloc_type_lookup
#define bfd_cgc32_bfd_reloc_name_lookup _bfd_norelocs_bfd_reloc_name_lookup
#define bfd_cgc32_bfd_link_add_symbols	cgc32_generic_link_add_symbols
#define cgc_info_to_howto		cgc_generic_info_to_howto
#define cgc_info_to_howto_rel		cgc_generic_info_to_howto_rel

#include "cgc32-target.h"
