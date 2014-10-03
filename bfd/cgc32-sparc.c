/* SPARC-specific support for 32-bit CGC
   Copyright 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
   2003, 2004, 2005, 2006, 2007, 2010, 2011
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
#include "bfdlink.h"
#include "libbfd.h"
#include "cgc-bfd.h"
#include "cgc/sparc.h"
#include "opcode/sparc.h"
#include "cgcxx-sparc.h"
#include "cgc-vxworks.h"

/* Support for core dump NOTE sections.  */

static bfd_boolean
cgc32_sparc_grok_psinfo (bfd *abfd, Cgc_Internal_Note *note)
{
  switch (note->descsz)
    {
    default:
      return FALSE;

    case 260:			/* Solaris prpsinfo_t.  */
      cgc_tdata (abfd)->core->program
	= _bfd_cgccore_strndup (abfd, note->descdata + 84, 16);
      cgc_tdata (abfd)->core->command
	= _bfd_cgccore_strndup (abfd, note->descdata + 100, 80);
      break;

    case 336:			/* Solaris psinfo_t.  */
      cgc_tdata (abfd)->core->program
	= _bfd_cgccore_strndup (abfd, note->descdata + 88, 16);
      cgc_tdata (abfd)->core->command
	= _bfd_cgccore_strndup (abfd, note->descdata + 104, 80);
      break;
    }

  return TRUE;
}

/* Functions for dealing with the e_flags field.

   We don't define set_private_flags or copy_private_bfd_data because
   the only currently defined values are based on the bfd mach number,
   so we use the latter instead and defer setting e_flags until the
   file is written out.  */

/* Merge backend specific data from an object file to the output
   object file when linking.  */

static bfd_boolean
cgc32_sparc_merge_private_bfd_data (bfd *ibfd, bfd *obfd)
{
  bfd_boolean error;
  unsigned long ibfd_mach;
  /* FIXME: This should not be static.  */
  static unsigned long previous_ibfd_e_flags = (unsigned long) -1;

  if (bfd_get_flavour (ibfd) != bfd_target_cgc_flavour
      || bfd_get_flavour (obfd) != bfd_target_cgc_flavour)
    return TRUE;

  error = FALSE;

  ibfd_mach = bfd_get_mach (ibfd);
  if (bfd_mach_sparc_64bit_p (ibfd_mach))
    {
      error = TRUE;
      (*_bfd_error_handler)
	(_("%B: compiled for a 64 bit system and target is 32 bit"), ibfd);
    }
  else if ((ibfd->flags & DYNAMIC) == 0)
    {
      if (bfd_get_mach (obfd) < ibfd_mach)
	bfd_set_arch_mach (obfd, bfd_arch_sparc, ibfd_mach);
    }

  if (((cgc_cgcheader (ibfd)->e_flags & EF_SPARC_LEDATA)
       != previous_ibfd_e_flags)
      && previous_ibfd_e_flags != (unsigned long) -1)
    {
      (*_bfd_error_handler)
	(_("%B: linking little endian files with big endian files"), ibfd);
      error = TRUE;
    }
  previous_ibfd_e_flags = cgc_cgcheader (ibfd)->e_flags & EF_SPARC_LEDATA;

  if (error)
    {
      bfd_set_error (bfd_error_bad_value);
      return FALSE;
    }

  return _bfd_sparc_cgc_merge_private_bfd_data (ibfd, obfd);
}

/* The final processing done just before writing out the object file.
   We need to set the e_machine field appropriately.  */

static void
cgc32_sparc_final_write_processing (bfd *abfd,
				    bfd_boolean linker ATTRIBUTE_UNUSED)
{
  switch (bfd_get_mach (abfd))
    {
    case bfd_mach_sparc :
    case bfd_mach_sparc_sparclet :
    case bfd_mach_sparc_sparclite :
      break; /* nothing to do */
    case bfd_mach_sparc_v8plus :
      cgc_cgcheader (abfd)->e_machine = EM_SPARC32PLUS;
      cgc_cgcheader (abfd)->e_flags &=~ EF_SPARC_32PLUS_MASK;
      cgc_cgcheader (abfd)->e_flags |= EF_SPARC_32PLUS;
      break;
    case bfd_mach_sparc_v8plusa :
      cgc_cgcheader (abfd)->e_machine = EM_SPARC32PLUS;
      cgc_cgcheader (abfd)->e_flags &=~ EF_SPARC_32PLUS_MASK;
      cgc_cgcheader (abfd)->e_flags |= EF_SPARC_32PLUS | EF_SPARC_SUN_US1;
      break;
    case bfd_mach_sparc_v8plusb :
      cgc_cgcheader (abfd)->e_machine = EM_SPARC32PLUS;
      cgc_cgcheader (abfd)->e_flags &=~ EF_SPARC_32PLUS_MASK;
      cgc_cgcheader (abfd)->e_flags |= EF_SPARC_32PLUS | EF_SPARC_SUN_US1
				       | EF_SPARC_SUN_US3;
      break;
    case bfd_mach_sparc_sparclite_le :
      cgc_cgcheader (abfd)->e_flags |= EF_SPARC_LEDATA;
      break;
    default :
      abort ();
      break;
    }
}

static enum cgc_reloc_type_class
cgc32_sparc_reloc_type_class (const struct bfd_link_info *info ATTRIBUTE_UNUSED,
			      const asection *rel_sec ATTRIBUTE_UNUSED,
			      const Cgc_Internal_Rela *rela)
{
  switch ((int) CGC32_R_TYPE (rela->r_info))
    {
    case R_SPARC_RELATIVE:
      return reloc_class_relative;
    case R_SPARC_JMP_SLOT:
      return reloc_class_plt;
    case R_SPARC_COPY:
      return reloc_class_copy;
    default:
      return reloc_class_normal;
    }
}

/* Hook called by the linker routine which adds symbols from an object
   file.  */

static bfd_boolean
cgc32_sparc_add_symbol_hook (bfd * abfd,
			     struct bfd_link_info * info ATTRIBUTE_UNUSED,
			     Cgc_Internal_Sym * sym,
			     const char ** namep ATTRIBUTE_UNUSED,
			     flagword * flagsp ATTRIBUTE_UNUSED,
			     asection ** secp ATTRIBUTE_UNUSED,
			     bfd_vma * valp ATTRIBUTE_UNUSED)
{
  if ((abfd->flags & DYNAMIC) == 0
      && (CGC_ST_TYPE (sym->st_info) == STT_GNU_IFUNC
	  || CGC_ST_BIND (sym->st_info) == STB_GNU_UNIQUE))
    cgc_tdata (info->output_bfd)->has_gnu_symbols = TRUE;
  return TRUE;
}

#define TARGET_BIG_SYM	bfd_cgc32_sparc_vec
#define TARGET_BIG_NAME	"cgc32-sparc"
#define CGC_ARCH	bfd_arch_sparc
#define CGC_TARGET_ID	SPARC_CGC_DATA
#define CGC_MACHINE_CODE EM_SPARC
#define CGC_MACHINE_ALT1 EM_SPARC32PLUS
#define CGC_MAXPAGESIZE 0x10000
#define CGC_COMMONPAGESIZE 0x2000

#define bfd_cgc32_bfd_merge_private_bfd_data \
					cgc32_sparc_merge_private_bfd_data
#define cgc_backend_final_write_processing \
					cgc32_sparc_final_write_processing
#define cgc_backend_grok_psinfo		cgc32_sparc_grok_psinfo
#define cgc_backend_reloc_type_class	cgc32_sparc_reloc_type_class

#define cgc_info_to_howto		_bfd_sparc_cgc_info_to_howto
#define bfd_cgc32_bfd_reloc_type_lookup	_bfd_sparc_cgc_reloc_type_lookup
#define bfd_cgc32_bfd_reloc_name_lookup \
  _bfd_sparc_cgc_reloc_name_lookup
#define bfd_cgc32_bfd_link_hash_table_create \
					_bfd_sparc_cgc_link_hash_table_create
#define bfd_cgc32_bfd_link_hash_table_free \
					_bfd_sparc_cgc_link_hash_table_free
#define bfd_cgc32_bfd_relax_section	_bfd_sparc_cgc_relax_section
#define bfd_cgc32_new_section_hook	_bfd_sparc_cgc_new_section_hook
#define cgc_backend_copy_indirect_symbol \
					_bfd_sparc_cgc_copy_indirect_symbol
#define cgc_backend_create_dynamic_sections \
					_bfd_sparc_cgc_create_dynamic_sections
#define cgc_backend_check_relocs	_bfd_sparc_cgc_check_relocs
#define cgc_backend_adjust_dynamic_symbol \
					_bfd_sparc_cgc_adjust_dynamic_symbol
#define cgc_backend_omit_section_dynsym	_bfd_sparc_cgc_omit_section_dynsym
#define cgc_backend_size_dynamic_sections \
					_bfd_sparc_cgc_size_dynamic_sections
#define cgc_backend_relocate_section	_bfd_sparc_cgc_relocate_section
#define cgc_backend_finish_dynamic_symbol \
					_bfd_sparc_cgc_finish_dynamic_symbol
#define cgc_backend_finish_dynamic_sections \
					_bfd_sparc_cgc_finish_dynamic_sections
#define bfd_cgc32_mkobject		_bfd_sparc_cgc_mkobject
#define cgc_backend_object_p		_bfd_sparc_cgc_object_p
#define cgc_backend_gc_mark_hook	_bfd_sparc_cgc_gc_mark_hook
#define cgc_backend_gc_sweep_hook       _bfd_sparc_cgc_gc_sweep_hook
#define cgc_backend_plt_sym_val		_bfd_sparc_cgc_plt_sym_val
#define cgc_backend_init_index_section	_bfd_cgc_init_1_index_section

#define cgc_backend_can_gc_sections 1
#define cgc_backend_can_refcount 1
#define cgc_backend_want_got_plt 0
#define cgc_backend_plt_readonly 0
#define cgc_backend_want_plt_sym 1
#define cgc_backend_got_header_size 4
#define cgc_backend_rela_normal 1

#define cgc_backend_post_process_headers	_bfd_cgc_set_osabi
#define cgc_backend_add_symbol_hook		cgc32_sparc_add_symbol_hook

#include "cgc32-target.h"

/* Solaris 2.  */

#undef	TARGET_BIG_SYM
#define	TARGET_BIG_SYM				bfd_cgc32_sparc_sol2_vec
#undef	TARGET_BIG_NAME
#define	TARGET_BIG_NAME				"cgc32-sparc-sol2"

#undef cgc32_bed
#define cgc32_bed				cgc32_sparc_sol2_bed

/* The 32-bit static TLS arena size is rounded to the nearest 8-byte
   boundary.  */
#undef cgc_backend_static_tls_alignment
#define cgc_backend_static_tls_alignment	8

#include "cgc32-target.h"

/* A wrapper around _bfd_sparc_cgc_link_hash_table_create that identifies
   the target system as VxWorks.  */

static struct bfd_link_hash_table *
cgc32_sparc_vxworks_link_hash_table_create (bfd *abfd)
{
  struct bfd_link_hash_table *ret;

  ret = _bfd_sparc_cgc_link_hash_table_create (abfd);
  if (ret)
    {
      struct _bfd_sparc_cgc_link_hash_table *htab;

      htab = (struct _bfd_sparc_cgc_link_hash_table *) ret;
      htab->is_vxworks = 1;
    }
  return ret;
}

/* A final_write_processing hook that does both the SPARC- and VxWorks-
   specific handling.  */

static void
cgc32_sparc_vxworks_final_write_processing (bfd *abfd, bfd_boolean linker)
{
  cgc32_sparc_final_write_processing (abfd, linker);
  cgc_vxworks_final_write_processing (abfd, linker);
}

#undef TARGET_BIG_SYM
#define TARGET_BIG_SYM	bfd_cgc32_sparc_vxworks_vec
#undef TARGET_BIG_NAME
#define TARGET_BIG_NAME	"cgc32-sparc-vxworks"

#undef CGC_MINPAGESIZE
#define CGC_MINPAGESIZE	0x1000

#undef bfd_cgc32_bfd_link_hash_table_create
#define bfd_cgc32_bfd_link_hash_table_create \
  cgc32_sparc_vxworks_link_hash_table_create

#undef cgc_backend_want_got_plt
#define cgc_backend_want_got_plt		1
#undef cgc_backend_plt_readonly
#define cgc_backend_plt_readonly		1
#undef cgc_backend_got_header_size
#define cgc_backend_got_header_size		12
#undef cgc_backend_add_symbol_hook
#define cgc_backend_add_symbol_hook \
  cgc_vxworks_add_symbol_hook
#undef cgc_backend_link_output_symbol_hook
#define cgc_backend_link_output_symbol_hook \
  cgc_vxworks_link_output_symbol_hook
#undef cgc_backend_emit_relocs
#define cgc_backend_emit_relocs \
  cgc_vxworks_emit_relocs
#undef cgc_backend_final_write_processing
#define cgc_backend_final_write_processing \
  cgc32_sparc_vxworks_final_write_processing
#undef cgc_backend_static_tls_alignment

#undef cgc32_bed
#define cgc32_bed				sparc_cgc_vxworks_bed

#include "cgc32-target.h"
