/* TILE-Gx CGC specific backend routines.
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

#include "cgc/common.h"
#include "cgc/internal.h"

extern enum cgc_reloc_type_class
tilegx_reloc_type_class (const struct bfd_link_info *,
			 const asection *,
			 const Cgc_Internal_Rela *);

extern reloc_howto_type *
tilegx_reloc_name_lookup (bfd *, const char *);

extern struct bfd_link_hash_table *
tilegx_cgc_link_hash_table_create (bfd *);

extern reloc_howto_type *
tilegx_reloc_type_lookup (bfd *, bfd_reloc_code_real_type);

extern void
tilegx_cgc_copy_indirect_symbol (struct bfd_link_info *,
				 struct cgc_link_hash_entry *,
				 struct cgc_link_hash_entry *);

extern bfd_boolean
tilegx_cgc_create_dynamic_sections (bfd *, struct bfd_link_info *);

extern bfd_boolean
tilegx_cgc_check_relocs (bfd *, struct bfd_link_info *,
			 asection *, const Cgc_Internal_Rela *);

extern bfd_boolean
tilegx_cgc_adjust_dynamic_symbol (struct bfd_link_info *,
				  struct cgc_link_hash_entry *);

extern bfd_boolean
tilegx_cgc_omit_section_dynsym (bfd *,
				struct bfd_link_info *,
				asection *);

extern bfd_boolean
tilegx_cgc_size_dynamic_sections (bfd *, struct bfd_link_info *);

extern bfd_boolean
tilegx_cgc_relocate_section (bfd *, struct bfd_link_info *,
			     bfd *, asection *,
			     bfd_byte *, Cgc_Internal_Rela *,
			     Cgc_Internal_Sym *,
			     asection **);

extern asection *
tilegx_cgc_gc_mark_hook (asection *,
			 struct bfd_link_info *,
			 Cgc_Internal_Rela *,
			 struct cgc_link_hash_entry *,
			 Cgc_Internal_Sym *);

extern bfd_boolean
tilegx_cgc_gc_sweep_hook (bfd *, struct bfd_link_info *,
			  asection *, const Cgc_Internal_Rela *);

extern bfd_vma
tilegx_cgc_plt_sym_val (bfd_vma, const asection *, const arelent *);

extern void
tilegx_info_to_howto_rela (bfd *, arelent *, Cgc_Internal_Rela *);

extern int
tilegx_additional_program_headers (bfd *, struct bfd_link_info *);

extern bfd_boolean
tilegx_cgc_finish_dynamic_symbol (bfd *,
				  struct bfd_link_info *,
				  struct cgc_link_hash_entry *,
				  Cgc_Internal_Sym *);

extern bfd_boolean
tilegx_cgc_finish_dynamic_sections (bfd *, struct bfd_link_info *);

extern bfd_boolean
_bfd_tilegx_cgc_merge_private_bfd_data (bfd *, bfd *);
