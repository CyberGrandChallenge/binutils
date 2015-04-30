/* TILE-Gx-specific support for 64-bit CGC.
   Copyright 2011 Free Software Foundation, Inc.

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
#include "cgcxx-tilegx.h"
#include "cgc64-tilegx.h"


/* Support for core dump NOTE sections.  */

static bfd_boolean
tilegx_cgc_grok_prstatus (bfd *abfd, Cgc_Internal_Note *note)
{
  int offset;
  size_t size;

  if (note->descsz != TILEGX_PRSTATUS_SIZEOF)
    return FALSE;

  /* pr_cursig */
  cgc_tdata (abfd)->core->signal =
    bfd_get_16 (abfd, note->descdata + TILEGX_PRSTATUS_OFFSET_PR_CURSIG);

  /* pr_pid */
  cgc_tdata (abfd)->core->pid =
    bfd_get_32 (abfd, note->descdata + TILEGX_PRSTATUS_OFFSET_PR_PID);

  /* pr_reg */
  offset = TILEGX_PRSTATUS_OFFSET_PR_REG;
  size   = TILEGX_GREGSET_T_SIZE;

  /* Make a ".reg/999" section.  */
  return _bfd_cgccore_make_pseudosection (abfd, ".reg",
					  size, note->descpos + offset);
}

static bfd_boolean
tilegx_cgc_grok_psinfo (bfd *abfd, Cgc_Internal_Note *note)
{
  if (note->descsz != TILEGX_PRPSINFO_SIZEOF)
    return FALSE;

  cgc_tdata (abfd)->core->program
    = _bfd_cgccore_strndup (abfd, note->descdata + TILEGX_PRPSINFO_OFFSET_PR_FNAME, 16);
  cgc_tdata (abfd)->core->command
    = _bfd_cgccore_strndup (abfd, note->descdata + TILEGX_PRPSINFO_OFFSET_PR_PSARGS, CGC_PR_PSARGS_SIZE);


  /* Note that for some reason, a spurious space is tacked
     onto the end of the args in some (at least one anyway)
     implementations, so strip it off if it exists.  */
  {
    char *command = cgc_tdata (abfd)->core->command;
    int n = strlen (command);

    if (0 < n && command[n - 1] == ' ')
      command[n - 1] = '\0';
  }

  return TRUE;
}


#define CGC_ARCH		bfd_arch_tilegx
#define CGC_TARGET_ID		TILEGX_CGC_DATA
#define CGC_MACHINE_CODE	EM_TILEGX
#define CGC_MAXPAGESIZE		0x10000
#define CGC_COMMONPAGESIZE	0x10000


#define TARGET_BIG_SYM          bfd_cgc64_tilegx_be_vec
#define TARGET_BIG_NAME         "cgc64-tilegx-be"
#define TARGET_LITTLE_SYM       bfd_cgc64_tilegx_le_vec
#define TARGET_LITTLE_NAME      "cgc64-tilegx-le"

#define cgc_backend_reloc_type_class	     tilegx_reloc_type_class

#define bfd_cgc64_bfd_reloc_name_lookup      tilegx_reloc_name_lookup
#define bfd_cgc64_bfd_link_hash_table_create tilegx_cgc_link_hash_table_create
#define bfd_cgc64_bfd_reloc_type_lookup	     tilegx_reloc_type_lookup
#define bfd_cgc64_bfd_merge_private_bfd_data \
  _bfd_tilegx_cgc_merge_private_bfd_data

#define cgc_backend_copy_indirect_symbol     tilegx_cgc_copy_indirect_symbol
#define cgc_backend_create_dynamic_sections  tilegx_cgc_create_dynamic_sections
#define cgc_backend_check_relocs	     tilegx_cgc_check_relocs
#define cgc_backend_adjust_dynamic_symbol    tilegx_cgc_adjust_dynamic_symbol
#define cgc_backend_omit_section_dynsym	     tilegx_cgc_omit_section_dynsym
#define cgc_backend_size_dynamic_sections    tilegx_cgc_size_dynamic_sections
#define cgc_backend_relocate_section	     tilegx_cgc_relocate_section
#define cgc_backend_finish_dynamic_symbol    tilegx_cgc_finish_dynamic_symbol
#define cgc_backend_finish_dynamic_sections  tilegx_cgc_finish_dynamic_sections
#define cgc_backend_gc_mark_hook	     tilegx_cgc_gc_mark_hook
#define cgc_backend_gc_sweep_hook            tilegx_cgc_gc_sweep_hook
#define cgc_backend_plt_sym_val		     tilegx_cgc_plt_sym_val
#define cgc_info_to_howto_rel                NULL
#define cgc_info_to_howto                    tilegx_info_to_howto_rela
#define cgc_backend_grok_prstatus            tilegx_cgc_grok_prstatus
#define cgc_backend_grok_psinfo              tilegx_cgc_grok_psinfo
#define cgc_backend_additional_program_headers tilegx_additional_program_headers

#define cgc_backend_init_index_section	_bfd_cgc_init_1_index_section

#define cgc_backend_can_gc_sections 1
#define cgc_backend_can_refcount 1
#define cgc_backend_want_got_plt 1
#define cgc_backend_plt_readonly 1
/* Align PLT mod 64 byte L2 line size. */
#define cgc_backend_plt_alignment 6
#define cgc_backend_want_plt_sym 1
#define cgc_backend_got_header_size 8
#define cgc_backend_rela_normal 1
#define cgc_backend_default_execstack 0

#include "cgc64-target.h"
