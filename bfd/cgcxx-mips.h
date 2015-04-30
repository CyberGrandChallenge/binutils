/* MIPS CGC specific backend routines.
   Copyright 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
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

#include "cgc/common.h"
#include "cgc/internal.h"
#include "cgc/mips.h"

extern bfd_boolean _bfd_mips_cgc_mkobject
  (bfd *);
extern bfd_boolean _bfd_mips_cgc_new_section_hook
  (bfd *, asection *);
extern void _bfd_mips_cgc_symbol_processing
  (bfd *, asymbol *);
extern unsigned int _bfd_mips_cgc_eh_frame_address_size
  (bfd *, asection *);
extern bfd_boolean _bfd_mips_cgc_name_local_section_symbols
  (bfd *);
extern bfd_boolean _bfd_mips_cgc_section_processing
  (bfd *, Cgc_Internal_Shdr *);
extern bfd_boolean _bfd_mips_cgc_section_from_shdr
  (bfd *, Cgc_Internal_Shdr *, const char *, int);
extern bfd_boolean _bfd_mips_cgc_fake_sections
  (bfd *, Cgc_Internal_Shdr *, asection *);
extern bfd_boolean _bfd_mips_cgc_section_from_bfd_section
  (bfd *, asection *, int *);
extern bfd_boolean _bfd_mips_cgc_add_symbol_hook
  (bfd *, struct bfd_link_info *, Cgc_Internal_Sym *,
   const char **, flagword *, asection **, bfd_vma *);
extern int _bfd_mips_cgc_link_output_symbol_hook
  (struct bfd_link_info *, const char *, Cgc_Internal_Sym *,
   asection *, struct cgc_link_hash_entry *);
extern bfd_boolean _bfd_mips_cgc_create_dynamic_sections
  (bfd *, struct bfd_link_info *);
extern bfd_boolean _bfd_mips_cgc_check_relocs
  (bfd *, struct bfd_link_info *, asection *, const Cgc_Internal_Rela *);
extern bfd_boolean _bfd_mips_cgc_adjust_dynamic_symbol
  (struct bfd_link_info *, struct cgc_link_hash_entry *);
extern bfd_boolean _bfd_mips_cgc_always_size_sections
  (bfd *, struct bfd_link_info *);
extern bfd_boolean _bfd_mips_cgc_size_dynamic_sections
  (bfd *, struct bfd_link_info *);
extern bfd_boolean _bfd_mips_cgc_relocate_section
  (bfd *, struct bfd_link_info *, bfd *, asection *, bfd_byte *,
   Cgc_Internal_Rela *, Cgc_Internal_Sym *, asection **);
extern bfd_boolean _bfd_mips_cgc_finish_dynamic_symbol
  (bfd *, struct bfd_link_info *, struct cgc_link_hash_entry *,
   Cgc_Internal_Sym *);
extern bfd_boolean _bfd_mips_vxworks_finish_dynamic_symbol
  (bfd *, struct bfd_link_info *, struct cgc_link_hash_entry *,
   Cgc_Internal_Sym *);
extern bfd_boolean _bfd_mips_cgc_finish_dynamic_sections
  (bfd *, struct bfd_link_info *);
extern void _bfd_mips_cgc_final_write_processing
  (bfd *, bfd_boolean);
extern int _bfd_mips_cgc_additional_program_headers
  (bfd *, struct bfd_link_info *);
extern bfd_boolean _bfd_mips_cgc_modify_segment_map
  (bfd *, struct bfd_link_info *);
extern asection * _bfd_mips_cgc_gc_mark_hook
  (asection *, struct bfd_link_info *, Cgc_Internal_Rela *,
   struct cgc_link_hash_entry *, Cgc_Internal_Sym *);
extern bfd_boolean _bfd_mips_cgc_gc_sweep_hook
  (bfd *, struct bfd_link_info *, asection *, const Cgc_Internal_Rela *);
extern void _bfd_mips_cgc_copy_indirect_symbol
  (struct bfd_link_info *, struct cgc_link_hash_entry *,
   struct cgc_link_hash_entry *);
extern bfd_boolean _bfd_mips_cgc_ignore_discarded_relocs
  (asection *);
extern bfd_boolean _bfd_mips_cgc_is_target_special_symbol
  (bfd *abfd, asymbol *sym);
extern bfd_boolean _bfd_mips_cgc_find_nearest_line
  (bfd *, asection *, asymbol **, bfd_vma, const char **,
   const char **, unsigned int *);
extern bfd_boolean _bfd_mips_cgc_find_inliner_info
  (bfd *, const char **, const char **, unsigned int *);
extern bfd_boolean _bfd_mips_cgc_set_section_contents
  (bfd *, asection *, const void *, file_ptr, bfd_size_type);
extern bfd_byte *_bfd_cgc_mips_get_relocated_section_contents
  (bfd *, struct bfd_link_info *, struct bfd_link_order *,
   bfd_byte *, bfd_boolean, asymbol **);
extern bfd_boolean _bfd_mips_cgc_relax_section
  (bfd *abfd, asection *sec, struct bfd_link_info *link_info,
   bfd_boolean *again);
extern struct bfd_link_hash_table *_bfd_mips_cgc_link_hash_table_create
  (bfd *);
extern struct bfd_link_hash_table *_bfd_mips_vxworks_link_hash_table_create
  (bfd *);
extern bfd_boolean _bfd_mips_cgc_final_link
  (bfd *, struct bfd_link_info *);
extern bfd_boolean _bfd_mips_cgc_merge_private_bfd_data
  (bfd *, bfd *);
extern bfd_boolean _bfd_mips_cgc_set_private_flags
  (bfd *, flagword);
extern bfd_boolean _bfd_mips_cgc_print_private_bfd_data
  (bfd *, void *);
extern bfd_boolean _bfd_mips_cgc_discard_info
  (bfd *, struct cgc_reloc_cookie *, struct bfd_link_info *);
extern bfd_boolean _bfd_mips_cgc_write_section
  (bfd *, struct bfd_link_info *, asection *, bfd_byte *);

extern bfd_boolean _bfd_mips_cgc_read_ecoff_info
  (bfd *, asection *, struct ecoff_debug_info *);
extern void _bfd_mips_cgc_reloc_unshuffle
  (bfd *, int, bfd_boolean, bfd_byte *);
extern void _bfd_mips_cgc_reloc_shuffle
  (bfd *, int, bfd_boolean, bfd_byte *);
extern bfd_reloc_status_type _bfd_mips_cgc_gprel16_with_gp
  (bfd *, asymbol *, arelent *, asection *, bfd_boolean, void *, bfd_vma);
extern bfd_reloc_status_type _bfd_mips_cgc32_gprel16_reloc
  (bfd *, arelent *, asymbol *, void *, asection *, bfd *, char **);
extern bfd_reloc_status_type _bfd_mips_cgc_hi16_reloc
  (bfd *, arelent *, asymbol *, void *, asection *, bfd *, char **);
extern bfd_reloc_status_type _bfd_mips_cgc_got16_reloc
  (bfd *, arelent *, asymbol *, void *, asection *, bfd *, char **);
extern bfd_reloc_status_type _bfd_mips_cgc_lo16_reloc
  (bfd *, arelent *, asymbol *, void *, asection *, bfd *, char **);
extern bfd_reloc_status_type _bfd_mips_cgc_generic_reloc
  (bfd *, arelent *, asymbol *, void *, asection *, bfd *, char **);
extern unsigned long _bfd_cgc_mips_mach
  (flagword);
extern bfd_boolean _bfd_mips_relax_section
  (bfd *, asection *, struct bfd_link_info *, bfd_boolean *);
extern bfd_vma _bfd_mips_cgc_sign_extend
  (bfd_vma, int);
extern void _bfd_mips_cgc_merge_symbol_attribute
  (struct cgc_link_hash_entry *, const Cgc_Internal_Sym *, bfd_boolean, bfd_boolean);
extern char *_bfd_mips_cgc_get_target_dtag (bfd_vma);
extern bfd_boolean _bfd_mips_cgc_ignore_undef_symbol
  (struct cgc_link_hash_entry *);
extern void _bfd_mips_cgc_use_plts_and_copy_relocs
  (struct bfd_link_info *);
extern void _bfd_mips_cgc_insn32
  (struct bfd_link_info *, bfd_boolean);
extern bfd_boolean _bfd_mips_cgc_init_stubs
  (struct bfd_link_info *,
   asection *(*) (const char *, asection *, asection *));
extern bfd_vma _bfd_mips_cgc_plt_sym_val
  (bfd_vma, const asection *, const arelent *rel);
extern long _bfd_mips_cgc_get_synthetic_symtab
  (bfd *, long, asymbol **, long, asymbol **, asymbol **);
extern void _bfd_mips_post_process_headers
  (bfd *abfd, struct bfd_link_info *link_info);

extern const struct bfd_cgc_special_section _bfd_mips_cgc_special_sections [];

extern bfd_boolean _bfd_mips_cgc_common_definition (Cgc_Internal_Sym *);

static inline bfd_boolean
gprel16_reloc_p (unsigned int r_type)
{
  return (r_type == R_MIPS_GPREL16
	  || r_type == R_MIPS16_GPREL
	  || r_type == R_MICROMIPS_GPREL16
	  || r_type == R_MICROMIPS_GPREL7_S2);
}

static inline bfd_boolean
literal_reloc_p (int r_type)
{
  return r_type == R_MIPS_LITERAL || r_type == R_MICROMIPS_LITERAL;
}

#define cgc_backend_common_definition   _bfd_mips_cgc_common_definition
#define cgc_backend_name_local_section_symbols \
  _bfd_mips_cgc_name_local_section_symbols
#define cgc_backend_special_sections _bfd_mips_cgc_special_sections
#define cgc_backend_eh_frame_address_size _bfd_mips_cgc_eh_frame_address_size
#define cgc_backend_merge_symbol_attribute  _bfd_mips_cgc_merge_symbol_attribute
#define cgc_backend_ignore_undef_symbol _bfd_mips_cgc_ignore_undef_symbol
#define cgc_backend_post_process_headers _bfd_mips_post_process_headers
