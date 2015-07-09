/* 32-bit CGC support for S+core.
   Copyright 2009 Free Software Foundation, Inc.
   Contributed by
   Brain.lin (brain.lin@sunplusct.com)
   Mei Ligang (ligang@sunnorth.com.cn)
   Pei-Lin Tsai (pltsai@sunplus.com)

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

extern void
s7_bfd_score_cgc_hide_symbol (struct bfd_link_info *,
                              struct cgc_link_hash_entry *,
                              bfd_boolean);

extern void
s7_bfd_score_info_to_howto (bfd *, arelent *, Cgc_Internal_Rela *);

extern bfd_boolean
s7_bfd_score_cgc_relocate_section (bfd *,
                                   struct bfd_link_info *,
                                   bfd *,
                                   asection *,
                                   bfd_byte *,
                                   Cgc_Internal_Rela *,
                                   Cgc_Internal_Sym *,
                                   asection **);

extern bfd_boolean
s7_bfd_score_cgc_check_relocs (bfd *,
                               struct bfd_link_info *,
                               asection *,
                               const Cgc_Internal_Rela *);

extern bfd_boolean
s7_bfd_score_cgc_add_symbol_hook (bfd *,
                                  struct bfd_link_info *,
                                  Cgc_Internal_Sym *,
                                  const char **,
                                  flagword *,
                                  asection **,
                                  bfd_vma *);

extern void
s7_bfd_score_cgc_symbol_processing (bfd *, asymbol *);

extern int
s7_bfd_score_cgc_link_output_symbol_hook (struct bfd_link_info *,
                                          const char *,
                                          Cgc_Internal_Sym *,
                                          asection *,
                                          struct cgc_link_hash_entry *);

extern bfd_boolean
s7_bfd_score_cgc_section_from_bfd_section (bfd *,
                                           asection *,
                                           int *);

extern bfd_boolean
s7_bfd_score_cgc_adjust_dynamic_symbol (struct bfd_link_info *,
                                        struct cgc_link_hash_entry *);

extern bfd_boolean
s7_bfd_score_cgc_always_size_sections (bfd *, struct bfd_link_info *);

extern bfd_boolean
s7_bfd_score_cgc_size_dynamic_sections (bfd *, struct bfd_link_info *);

extern bfd_boolean
s7_bfd_score_cgc_create_dynamic_sections (bfd *, struct bfd_link_info *);

extern bfd_boolean
s7_bfd_score_cgc_finish_dynamic_symbol (bfd *,
                                        struct bfd_link_info *,
                                        struct cgc_link_hash_entry *,
                                        Cgc_Internal_Sym *);

extern bfd_boolean
s7_bfd_score_cgc_finish_dynamic_sections (bfd *, struct bfd_link_info *);

extern bfd_boolean
s7_bfd_score_cgc_fake_sections (bfd *,
                                Cgc_Internal_Shdr *,
                                asection *);

extern bfd_boolean
s7_bfd_score_cgc_section_processing (bfd *, Cgc_Internal_Shdr *);

extern bfd_boolean
s7_bfd_score_cgc_write_section (bfd *, asection *, bfd_byte *);

extern void
s7_bfd_score_cgc_copy_indirect_symbol (struct bfd_link_info *,
                                       struct cgc_link_hash_entry *,
                                       struct cgc_link_hash_entry *);

extern bfd_boolean
s7_bfd_score_cgc_discard_info (bfd *, struct cgc_reloc_cookie *,
                               struct bfd_link_info *);

extern bfd_boolean
s7_bfd_score_cgc_ignore_discarded_relocs (asection *);

extern asection *
s7_bfd_score_cgc_gc_mark_hook (asection *,
                               struct bfd_link_info *,
                               Cgc_Internal_Rela *,
                               struct cgc_link_hash_entry *,
                               Cgc_Internal_Sym *);

extern bfd_boolean
s7_bfd_score_cgc_grok_prstatus (bfd *, Cgc_Internal_Note *);

extern bfd_boolean
s7_bfd_score_cgc_grok_psinfo (bfd *, Cgc_Internal_Note *);

extern reloc_howto_type *
s7_cgc32_score_reloc_type_lookup (bfd *, bfd_reloc_code_real_type);

extern struct bfd_link_hash_table *
s7_cgc32_score_link_hash_table_create (bfd *);

extern bfd_boolean
s7_cgc32_score_print_private_bfd_data (bfd *, void *);

extern bfd_boolean
s7_cgc32_score_merge_private_bfd_data (bfd *, bfd *);

extern bfd_boolean
s7_cgc32_score_new_section_hook (bfd *, asection *);

extern bfd_boolean
_bfd_score_cgc_common_definition (Cgc_Internal_Sym *);

#define cgc_backend_common_definition   _bfd_score_cgc_common_definition
