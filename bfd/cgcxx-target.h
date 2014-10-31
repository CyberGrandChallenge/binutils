/* Target definitions for NN-bit CGC
   Copyright 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
   2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012
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


/* This structure contains everything that BFD knows about a target.
   It includes things like its byte order, name, what routines to call
   to do various operations, etc.  Every BFD points to a target structure
   with its "xvec" member.

   There are two such structures here:  one for big-endian machines and
   one for little-endian machines.   */

#ifndef bfd_cgcNN_close_and_cleanup
#define	bfd_cgcNN_close_and_cleanup _bfd_cgc_close_and_cleanup
#endif
#ifndef bfd_cgcNN_bfd_free_cached_info
#define bfd_cgcNN_bfd_free_cached_info _bfd_free_cached_info
#endif
#ifndef bfd_cgcNN_get_section_contents
#define bfd_cgcNN_get_section_contents _bfd_generic_get_section_contents
#endif

#define bfd_cgcNN_canonicalize_dynamic_symtab \
  _bfd_cgc_canonicalize_dynamic_symtab
#ifndef bfd_cgcNN_get_synthetic_symtab
#define bfd_cgcNN_get_synthetic_symtab \
  _bfd_cgc_get_synthetic_symtab
#endif
#ifndef bfd_cgcNN_canonicalize_reloc
#define bfd_cgcNN_canonicalize_reloc	_bfd_cgc_canonicalize_reloc
#endif
#ifndef bfd_cgcNN_find_nearest_line
#define bfd_cgcNN_find_nearest_line	_bfd_cgc_find_nearest_line
#endif
#ifndef bfd_cgcNN_find_inliner_info
#define bfd_cgcNN_find_inliner_info	_bfd_cgc_find_inliner_info
#endif
#define bfd_cgcNN_read_minisymbols	_bfd_cgc_read_minisymbols
#define bfd_cgcNN_minisymbol_to_symbol	_bfd_cgc_minisymbol_to_symbol
#define bfd_cgcNN_get_dynamic_symtab_upper_bound \
  _bfd_cgc_get_dynamic_symtab_upper_bound
#define bfd_cgcNN_get_lineno		_bfd_cgc_get_lineno
#ifndef bfd_cgcNN_get_reloc_upper_bound
#define bfd_cgcNN_get_reloc_upper_bound _bfd_cgc_get_reloc_upper_bound
#endif
#ifndef bfd_cgcNN_get_symbol_info
#define bfd_cgcNN_get_symbol_info	_bfd_cgc_get_symbol_info
#endif
#define bfd_cgcNN_canonicalize_symtab	_bfd_cgc_canonicalize_symtab
#define bfd_cgcNN_get_symtab_upper_bound _bfd_cgc_get_symtab_upper_bound
#define bfd_cgcNN_make_empty_symbol	_bfd_cgc_make_empty_symbol
#ifndef bfd_cgcNN_new_section_hook
#define bfd_cgcNN_new_section_hook	_bfd_cgc_new_section_hook
#endif
#define bfd_cgcNN_set_arch_mach		_bfd_cgc_set_arch_mach
#ifndef bfd_cgcNN_set_section_contents
#define bfd_cgcNN_set_section_contents	_bfd_cgc_set_section_contents
#endif
#define bfd_cgcNN_sizeof_headers	_bfd_cgc_sizeof_headers
#define bfd_cgcNN_write_object_contents _bfd_cgc_write_object_contents
#define bfd_cgcNN_write_corefile_contents _bfd_cgc_write_corefile_contents

#define bfd_cgcNN_get_section_contents_in_window \
  _bfd_generic_get_section_contents_in_window

#ifndef cgc_backend_can_refcount
#define cgc_backend_can_refcount 0
#endif
#ifndef cgc_backend_want_got_plt
#define cgc_backend_want_got_plt 0
#endif
#ifndef cgc_backend_plt_readonly
#define cgc_backend_plt_readonly 0
#endif
#ifndef cgc_backend_want_plt_sym
#define cgc_backend_want_plt_sym 0
#endif
#ifndef cgc_backend_plt_not_loaded
#define cgc_backend_plt_not_loaded 0
#endif
#ifndef cgc_backend_plt_alignment
#define cgc_backend_plt_alignment 2
#endif
#ifndef cgc_backend_want_dynbss
#define cgc_backend_want_dynbss 1
#endif
#ifndef cgc_backend_want_p_paddr_set_to_zero
#define cgc_backend_want_p_paddr_set_to_zero 0
#endif
#ifndef cgc_backend_default_execstack
#define cgc_backend_default_execstack 1
#endif
#ifndef cgc_backend_stack_align
#define cgc_backend_stack_align 16
#endif

#define bfd_cgcNN_bfd_debug_info_start	bfd_void
#define bfd_cgcNN_bfd_debug_info_end	bfd_void
#define bfd_cgcNN_bfd_debug_info_accumulate \
  ((void (*) (bfd*, struct bfd_section *)) bfd_void)

#ifndef bfd_cgcNN_bfd_get_relocated_section_contents
#define bfd_cgcNN_bfd_get_relocated_section_contents \
  bfd_generic_get_relocated_section_contents
#endif

#ifndef bfd_cgcNN_bfd_relax_section
#define bfd_cgcNN_bfd_relax_section bfd_generic_relax_section
#endif

#ifndef cgc_backend_can_gc_sections
#define cgc_backend_can_gc_sections 0
#endif
#ifndef cgc_backend_can_refcount
#define cgc_backend_can_refcount 0
#endif
#ifndef cgc_backend_want_got_sym
#define cgc_backend_want_got_sym 1
#endif
#ifndef cgc_backend_gc_keep
#define cgc_backend_gc_keep		_bfd_cgc_gc_keep
#endif
#ifndef cgc_backend_gc_mark_dynamic_ref
#define cgc_backend_gc_mark_dynamic_ref	bfd_cgc_gc_mark_dynamic_ref_symbol
#endif
#ifndef cgc_backend_gc_mark_hook
#define cgc_backend_gc_mark_hook	_bfd_cgc_gc_mark_hook
#endif
#ifndef cgc_backend_gc_mark_extra_sections
#define cgc_backend_gc_mark_extra_sections _bfd_cgc_gc_mark_extra_sections
#endif
#ifndef cgc_backend_gc_sweep_hook
#define cgc_backend_gc_sweep_hook	NULL
#endif
#ifndef bfd_cgcNN_bfd_gc_sections
#define bfd_cgcNN_bfd_gc_sections bfd_cgc_gc_sections
#endif

#ifndef bfd_cgcNN_bfd_merge_sections
#define bfd_cgcNN_bfd_merge_sections \
  _bfd_cgc_merge_sections
#endif

#ifndef bfd_cgcNN_bfd_is_group_section
#define bfd_cgcNN_bfd_is_group_section bfd_cgc_is_group_section
#endif

#ifndef bfd_cgcNN_bfd_discard_group
#define bfd_cgcNN_bfd_discard_group bfd_generic_discard_group
#endif

#ifndef bfd_cgcNN_section_already_linked
#define bfd_cgcNN_section_already_linked \
  _bfd_cgc_section_already_linked
#endif

#ifndef bfd_cgcNN_bfd_define_common_symbol
#define bfd_cgcNN_bfd_define_common_symbol bfd_generic_define_common_symbol
#endif

#ifndef bfd_cgcNN_bfd_lookup_section_flags
#define bfd_cgcNN_bfd_lookup_section_flags bfd_cgc_lookup_section_flags
#endif

#ifndef bfd_cgcNN_bfd_make_debug_symbol
#define bfd_cgcNN_bfd_make_debug_symbol \
  ((asymbol * (*) (bfd *, void *, unsigned long)) bfd_nullvoidptr)
#endif

#ifndef bfd_cgcNN_bfd_copy_private_symbol_data
#define bfd_cgcNN_bfd_copy_private_symbol_data \
  _bfd_cgc_copy_private_symbol_data
#endif

#ifndef bfd_cgcNN_bfd_copy_private_section_data
#define bfd_cgcNN_bfd_copy_private_section_data \
  _bfd_cgc_copy_private_section_data
#endif
#ifndef bfd_cgcNN_bfd_copy_private_header_data
#define bfd_cgcNN_bfd_copy_private_header_data \
  _bfd_cgc_copy_private_header_data
#endif
#ifndef bfd_cgcNN_bfd_copy_private_bfd_data
#define bfd_cgcNN_bfd_copy_private_bfd_data \
  _bfd_cgc_copy_private_bfd_data
#endif
#ifndef bfd_cgcNN_bfd_print_private_bfd_data
#define bfd_cgcNN_bfd_print_private_bfd_data \
  _bfd_cgc_print_private_bfd_data
#endif
#ifndef bfd_cgcNN_bfd_merge_private_bfd_data
#define bfd_cgcNN_bfd_merge_private_bfd_data \
  ((bfd_boolean (*) (bfd *, bfd *)) bfd_true)
#endif
#ifndef bfd_cgcNN_bfd_set_private_flags
#define bfd_cgcNN_bfd_set_private_flags \
  ((bfd_boolean (*) (bfd *, flagword)) bfd_true)
#endif
#ifndef bfd_cgcNN_bfd_is_local_label_name
#define bfd_cgcNN_bfd_is_local_label_name _bfd_cgc_is_local_label_name
#endif
#ifndef bfd_cgcNN_bfd_is_target_special_symbol
#define bfd_cgcNN_bfd_is_target_special_symbol \
  ((bfd_boolean (*) (bfd *, asymbol *)) bfd_false)
#endif

#ifndef bfd_cgcNN_get_dynamic_reloc_upper_bound
#define bfd_cgcNN_get_dynamic_reloc_upper_bound \
  _bfd_cgc_get_dynamic_reloc_upper_bound
#endif
#ifndef bfd_cgcNN_canonicalize_dynamic_reloc
#define bfd_cgcNN_canonicalize_dynamic_reloc \
  _bfd_cgc_canonicalize_dynamic_reloc
#endif

#ifdef cgc_backend_relocate_section
#ifndef bfd_cgcNN_bfd_link_hash_table_create
#define bfd_cgcNN_bfd_link_hash_table_create _bfd_cgc_link_hash_table_create
#endif
#ifndef bfd_cgcNN_bfd_link_hash_table_free
#define bfd_cgcNN_bfd_link_hash_table_free _bfd_cgc_link_hash_table_free
#endif
#ifndef bfd_cgcNN_bfd_link_add_symbols
#define bfd_cgcNN_bfd_link_add_symbols	bfd_cgc_link_add_symbols
#endif
#ifndef bfd_cgcNN_bfd_final_link
#define bfd_cgcNN_bfd_final_link	bfd_cgc_final_link
#endif
#else /* ! defined (cgc_backend_relocate_section) */
/* If no backend relocate_section routine, use the generic linker.
   Note - this will prevent the port from being able to use some of
   the other features of the CGC linker, because the generic hash structure
   does not have the fields needed by the CGC linker.  In particular it
   means that linking directly to S-records will not work.  */
#ifndef bfd_cgcNN_bfd_link_hash_table_create
#define bfd_cgcNN_bfd_link_hash_table_create \
  _bfd_generic_link_hash_table_create
#endif
#ifndef bfd_cgcNN_bfd_link_hash_table_free
#define bfd_cgcNN_bfd_link_hash_table_free _bfd_generic_link_hash_table_free
#endif
#ifndef bfd_cgcNN_bfd_link_add_symbols
#define bfd_cgcNN_bfd_link_add_symbols	_bfd_generic_link_add_symbols
#endif
#ifndef bfd_cgcNN_bfd_final_link
#define bfd_cgcNN_bfd_final_link	_bfd_generic_final_link
#endif
#endif /* ! defined (cgc_backend_relocate_section) */

#ifndef bfd_cgcNN_bfd_link_just_syms
#define bfd_cgcNN_bfd_link_just_syms	_bfd_cgc_link_just_syms
#endif

#ifndef bfd_cgcNN_bfd_copy_link_hash_symbol_type
#define bfd_cgcNN_bfd_copy_link_hash_symbol_type \
  _bfd_cgc_copy_link_hash_symbol_type
#endif

#ifndef bfd_cgcNN_bfd_link_split_section
#define bfd_cgcNN_bfd_link_split_section _bfd_generic_link_split_section
#endif

#ifndef bfd_cgcNN_archive_p
#define bfd_cgcNN_archive_p bfd_generic_archive_p
#endif

#ifndef bfd_cgcNN_write_archive_contents
#define bfd_cgcNN_write_archive_contents _bfd_write_archive_contents
#endif

#ifndef bfd_cgcNN_mkobject
#define bfd_cgcNN_mkobject bfd_cgc_make_object
#endif

#ifndef bfd_cgcNN_mkcorefile
#define bfd_cgcNN_mkcorefile bfd_cgc_mkcorefile
#endif

#ifndef bfd_cgcNN_mkarchive
#define bfd_cgcNN_mkarchive _bfd_generic_mkarchive
#endif

#ifndef bfd_cgcNN_print_symbol
#define bfd_cgcNN_print_symbol bfd_cgc_print_symbol
#endif

#ifndef cgc_symbol_leading_char
#define cgc_symbol_leading_char 0
#endif

#ifndef cgc_info_to_howto
#define cgc_info_to_howto 0
#endif

#ifndef cgc_info_to_howto_rel
#define cgc_info_to_howto_rel 0
#endif

#ifndef cgc_backend_arch_data
#define cgc_backend_arch_data NULL
#endif

#ifndef CGC_TARGET_ID
#define CGC_TARGET_ID	GENERIC_CGC_DATA
#endif

#ifndef CGC_OSABI
#define CGC_OSABI CGCOSABI_NONE
#endif

#ifndef CGC_MAXPAGESIZE
# error CGC_MAXPAGESIZE is not defined
#define CGC_MAXPAGESIZE 1
#endif

#ifndef CGC_COMMONPAGESIZE
#define CGC_COMMONPAGESIZE CGC_MAXPAGESIZE
#endif

#ifndef CGC_MINPAGESIZE
#define CGC_MINPAGESIZE CGC_COMMONPAGESIZE
#endif

#if CGC_COMMONPAGESIZE > CGC_MAXPAGESIZE
# error CGC_COMMONPAGESIZE > CGC_MAXPAGESIZE
#endif
#if CGC_MINPAGESIZE > CGC_COMMONPAGESIZE
# error CGC_MINPAGESIZE > CGC_COMMONPAGESIZE
#endif

#ifndef CGC_DYNAMIC_SEC_FLAGS
/* Note that we set the SEC_IN_MEMORY flag for these sections.  */
#define CGC_DYNAMIC_SEC_FLAGS			\
  (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS	\
   | SEC_IN_MEMORY | SEC_LINKER_CREATED)
#endif

#ifndef cgc_backend_collect
#define cgc_backend_collect FALSE
#endif
#ifndef cgc_backend_type_change_ok
#define cgc_backend_type_change_ok FALSE
#endif

#ifndef cgc_backend_sym_is_global
#define cgc_backend_sym_is_global	0
#endif
#ifndef cgc_backend_object_p
#define cgc_backend_object_p		0
#endif
#ifndef cgc_backend_symbol_processing
#define cgc_backend_symbol_processing	0
#endif
#ifndef cgc_backend_symbol_table_processing
#define cgc_backend_symbol_table_processing	0
#endif
#ifndef cgc_backend_get_symbol_type
#define cgc_backend_get_symbol_type 0
#endif
#ifndef cgc_backend_archive_symbol_lookup
#define cgc_backend_archive_symbol_lookup _bfd_cgc_archive_symbol_lookup
#endif
#ifndef cgc_backend_name_local_section_symbols
#define cgc_backend_name_local_section_symbols	0
#endif
#ifndef cgc_backend_section_processing
#define cgc_backend_section_processing	0
#endif
#ifndef cgc_backend_section_from_shdr
#define cgc_backend_section_from_shdr	_bfd_cgc_make_section_from_shdr
#endif
#ifndef cgc_backend_section_flags
#define cgc_backend_section_flags	0
#endif
#ifndef cgc_backend_get_sec_type_attr
#define cgc_backend_get_sec_type_attr	_bfd_cgc_get_sec_type_attr
#endif
#ifndef cgc_backend_section_from_phdr
#define cgc_backend_section_from_phdr	_bfd_cgc_make_section_from_phdr
#endif
#ifndef cgc_backend_fake_sections
#define cgc_backend_fake_sections	0
#endif
#ifndef cgc_backend_section_from_bfd_section
#define cgc_backend_section_from_bfd_section	0
#endif
#ifndef cgc_backend_add_symbol_hook
#define cgc_backend_add_symbol_hook	0
#endif
#ifndef cgc_backend_link_output_symbol_hook
#define cgc_backend_link_output_symbol_hook 0
#endif
#ifndef cgc_backend_create_dynamic_sections
#define cgc_backend_create_dynamic_sections 0
#endif
#ifndef cgc_backend_omit_section_dynsym
#define cgc_backend_omit_section_dynsym _bfd_cgc_link_omit_section_dynsym
#endif
#ifndef cgc_backend_relocs_compatible
#define cgc_backend_relocs_compatible _bfd_cgc_default_relocs_compatible
#endif
#ifndef cgc_backend_check_relocs
#define cgc_backend_check_relocs	0
#endif
#ifndef cgc_backend_check_directives
#define cgc_backend_check_directives	0
#endif
#ifndef cgc_backend_notice_as_needed
#define cgc_backend_notice_as_needed	_bfd_cgc_notice_as_needed
#endif
#ifndef cgc_backend_adjust_dynamic_symbol
#define cgc_backend_adjust_dynamic_symbol 0
#endif
#ifndef cgc_backend_always_size_sections
#define cgc_backend_always_size_sections 0
#endif
#ifndef cgc_backend_size_dynamic_sections
#define cgc_backend_size_dynamic_sections 0
#endif
#ifndef cgc_backend_init_index_section
#define cgc_backend_init_index_section \
 ((void (*) (bfd *, struct bfd_link_info *)) bfd_void)
#endif
#ifndef cgc_backend_relocate_section
#define cgc_backend_relocate_section	0
#endif
#ifndef cgc_backend_finish_dynamic_symbol
#define cgc_backend_finish_dynamic_symbol	0
#endif
#ifndef cgc_backend_finish_dynamic_sections
#define cgc_backend_finish_dynamic_sections	0
#endif
#ifndef cgc_backend_begin_write_processing
#define cgc_backend_begin_write_processing	0
#endif
#ifndef cgc_backend_final_write_processing
#define cgc_backend_final_write_processing	0
#endif
#ifndef cgc_backend_additional_program_headers
#define cgc_backend_additional_program_headers	0
#endif
#ifndef cgc_backend_modify_segment_map
#define cgc_backend_modify_segment_map	0
#endif
#ifndef cgc_backend_modify_program_headers
#define cgc_backend_modify_program_headers	0
#endif
#ifndef cgc_backend_ecoff_debug_swap
#define cgc_backend_ecoff_debug_swap	0
#endif
#ifndef cgc_backend_bfd_from_remote_memory
#define cgc_backend_bfd_from_remote_memory _bfd_cgcNN_bfd_from_remote_memory
#endif
#ifndef cgc_backend_got_header_size
#define cgc_backend_got_header_size	0
#endif
#ifndef cgc_backend_got_elt_size
#define cgc_backend_got_elt_size _bfd_cgc_default_got_elt_size
#endif
#ifndef cgc_backend_obj_attrs_vendor
#define cgc_backend_obj_attrs_vendor		NULL
#endif
#ifndef cgc_backend_obj_attrs_section
#define cgc_backend_obj_attrs_section		NULL
#endif
#ifndef cgc_backend_obj_attrs_arg_type
#define cgc_backend_obj_attrs_arg_type		NULL
#endif
#ifndef cgc_backend_obj_attrs_section_type
#define cgc_backend_obj_attrs_section_type		SHT_GNU_ATTRIBUTES
#endif
#ifndef cgc_backend_obj_attrs_order
#define cgc_backend_obj_attrs_order		NULL
#endif
#ifndef cgc_backend_obj_attrs_handle_unknown
#define cgc_backend_obj_attrs_handle_unknown	NULL
#endif
#ifndef cgc_backend_static_tls_alignment
#define cgc_backend_static_tls_alignment	1
#endif
#ifndef cgc_backend_post_process_headers
#define cgc_backend_post_process_headers	NULL
#endif
#ifndef cgc_backend_print_symbol_all
#define cgc_backend_print_symbol_all		NULL
#endif
#ifndef cgc_backend_output_arch_local_syms
#define cgc_backend_output_arch_local_syms	NULL
#endif
#ifndef cgc_backend_output_arch_syms
#define cgc_backend_output_arch_syms		NULL
#endif
#ifndef cgc_backend_copy_indirect_symbol
#define cgc_backend_copy_indirect_symbol  _bfd_cgc_link_hash_copy_indirect
#endif
#ifndef cgc_backend_hide_symbol
#define cgc_backend_hide_symbol		_bfd_cgc_link_hash_hide_symbol
#endif
#ifndef cgc_backend_fixup_symbol
#define cgc_backend_fixup_symbol		NULL
#endif
#ifndef cgc_backend_merge_symbol_attribute
#define cgc_backend_merge_symbol_attribute	NULL
#endif
#ifndef cgc_backend_get_target_dtag
#define cgc_backend_get_target_dtag		NULL
#endif
#ifndef cgc_backend_ignore_undef_symbol
#define cgc_backend_ignore_undef_symbol		NULL
#endif
#ifndef cgc_backend_emit_relocs
#define cgc_backend_emit_relocs			_bfd_cgc_link_output_relocs
#endif
#ifndef cgc_backend_count_relocs
#define cgc_backend_count_relocs		NULL
#endif
#ifndef cgc_backend_grok_prstatus
#define cgc_backend_grok_prstatus		NULL
#endif
#ifndef cgc_backend_grok_psinfo
#define cgc_backend_grok_psinfo			NULL
#endif
#ifndef cgc_backend_write_core_note
#define cgc_backend_write_core_note		NULL
#endif
#ifndef cgc_backend_lookup_section_flags_hook
#define cgc_backend_lookup_section_flags_hook	NULL
#endif
#ifndef cgc_backend_reloc_type_class
#define cgc_backend_reloc_type_class		_bfd_cgc_reloc_type_class
#endif
#ifndef cgc_backend_discard_info
#define cgc_backend_discard_info		NULL
#endif
#ifndef cgc_backend_ignore_discarded_relocs
#define cgc_backend_ignore_discarded_relocs	NULL
#endif
#ifndef cgc_backend_action_discarded
#define cgc_backend_action_discarded _bfd_cgc_default_action_discarded
#endif
#ifndef cgc_backend_eh_frame_address_size
#define cgc_backend_eh_frame_address_size _bfd_cgc_eh_frame_address_size
#endif
#ifndef cgc_backend_can_make_relative_eh_frame
#define cgc_backend_can_make_relative_eh_frame	_bfd_cgc_can_make_relative
#endif
#ifndef cgc_backend_can_make_lsda_relative_eh_frame
#define cgc_backend_can_make_lsda_relative_eh_frame	_bfd_cgc_can_make_relative
#endif
#ifndef cgc_backend_encode_eh_address
#define cgc_backend_encode_eh_address		_bfd_cgc_encode_eh_address
#endif
#ifndef cgc_backend_write_section
#define cgc_backend_write_section		NULL
#endif
#ifndef cgc_backend_mips_irix_compat
#define cgc_backend_mips_irix_compat		NULL
#endif
#ifndef cgc_backend_mips_rtype_to_howto
#define cgc_backend_mips_rtype_to_howto		NULL
#endif

/* Previously, backends could only use SHT_REL or SHT_RELA relocation
   sections, but not both.  They defined USE_REL to indicate SHT_REL
   sections, and left it undefined to indicated SHT_RELA sections.
   For backwards compatibility, we still support this usage.  */
#ifndef USE_REL
#define USE_REL 0
#endif

/* Use these in new code.  */
#ifndef cgc_backend_may_use_rel_p
#define cgc_backend_may_use_rel_p USE_REL
#endif
#ifndef cgc_backend_may_use_rela_p
#define cgc_backend_may_use_rela_p !USE_REL
#endif
#ifndef cgc_backend_default_use_rela_p
#define cgc_backend_default_use_rela_p !USE_REL
#endif
#ifndef cgc_backend_rela_plts_and_copies_p
#define cgc_backend_rela_plts_and_copies_p cgc_backend_default_use_rela_p
#endif

#ifndef cgc_backend_rela_normal
#define cgc_backend_rela_normal 0
#endif

#ifndef cgc_backend_plt_sym_val
#define cgc_backend_plt_sym_val NULL
#endif
#ifndef cgc_backend_relplt_name
#define cgc_backend_relplt_name NULL
#endif

#ifndef CGC_MACHINE_ALT1
#define CGC_MACHINE_ALT1 0
#endif

#ifndef CGC_MACHINE_ALT2
#define CGC_MACHINE_ALT2 0
#endif

#ifndef cgc_backend_size_info
#define cgc_backend_size_info _bfd_cgcNN_size_info
#endif

#ifndef cgc_backend_special_sections
#define cgc_backend_special_sections NULL
#endif

#ifndef cgc_backend_sign_extend_vma
#define cgc_backend_sign_extend_vma 0
#endif

#ifndef cgc_backend_link_order_error_handler
#define cgc_backend_link_order_error_handler _bfd_default_error_handler
#endif

#ifndef cgc_backend_common_definition
#define cgc_backend_common_definition _bfd_cgc_common_definition
#endif

#ifndef cgc_backend_common_section_index
#define cgc_backend_common_section_index _bfd_cgc_common_section_index
#endif

#ifndef cgc_backend_common_section
#define cgc_backend_common_section _bfd_cgc_common_section
#endif

#ifndef cgc_backend_merge_symbol
#define cgc_backend_merge_symbol NULL
#endif

#ifndef cgc_backend_hash_symbol
#define cgc_backend_hash_symbol _bfd_cgc_hash_symbol
#endif

#ifndef cgc_backend_is_function_type
#define cgc_backend_is_function_type _bfd_cgc_is_function_type
#endif

#ifndef cgc_backend_maybe_function_sym
#define cgc_backend_maybe_function_sym _bfd_cgc_maybe_function_sym
#endif

#ifndef cgc_match_priority
#define cgc_match_priority \
  (CGC_ARCH == bfd_arch_unknown ? 2 : CGC_OSABI == CGCOSABI_NONE ? 1 : 0)
#endif

extern const struct cgc_size_info _bfd_cgcNN_size_info;

static struct cgc_backend_data cgcNN_bed =
{
  CGC_ARCH,			/* arch */
  CGC_TARGET_ID,		/* target_id */
  CGC_MACHINE_CODE,		/* cgc_machine_code */
  CGC_OSABI,			/* cgc_osabi  */
  CGC_MAXPAGESIZE,		/* maxpagesize */
  CGC_MINPAGESIZE,		/* minpagesize */
  CGC_COMMONPAGESIZE,		/* commonpagesize */
  CGC_DYNAMIC_SEC_FLAGS,	/* dynamic_sec_flags */
  cgc_backend_arch_data,
  cgc_info_to_howto,
  cgc_info_to_howto_rel,
  cgc_backend_sym_is_global,
  cgc_backend_object_p,
  cgc_backend_symbol_processing,
  cgc_backend_symbol_table_processing,
  cgc_backend_get_symbol_type,
  cgc_backend_archive_symbol_lookup,
  cgc_backend_name_local_section_symbols,
  cgc_backend_section_processing,
  cgc_backend_section_from_shdr,
  cgc_backend_section_flags,
  cgc_backend_get_sec_type_attr,
  cgc_backend_section_from_phdr,
  cgc_backend_fake_sections,
  cgc_backend_section_from_bfd_section,
  cgc_backend_add_symbol_hook,
  cgc_backend_link_output_symbol_hook,
  cgc_backend_create_dynamic_sections,
  cgc_backend_omit_section_dynsym,
  cgc_backend_relocs_compatible,
  cgc_backend_check_relocs,
  cgc_backend_check_directives,
  cgc_backend_notice_as_needed,
  cgc_backend_adjust_dynamic_symbol,
  cgc_backend_always_size_sections,
  cgc_backend_size_dynamic_sections,
  cgc_backend_init_index_section,
  cgc_backend_relocate_section,
  cgc_backend_finish_dynamic_symbol,
  cgc_backend_finish_dynamic_sections,
  cgc_backend_begin_write_processing,
  cgc_backend_final_write_processing,
  cgc_backend_additional_program_headers,
  cgc_backend_modify_segment_map,
  cgc_backend_modify_program_headers,
  cgc_backend_gc_keep,
  cgc_backend_gc_mark_dynamic_ref,
  cgc_backend_gc_mark_hook,
  cgc_backend_gc_mark_extra_sections,
  cgc_backend_gc_sweep_hook,
  cgc_backend_post_process_headers,
  cgc_backend_print_symbol_all,
  cgc_backend_output_arch_local_syms,
  cgc_backend_output_arch_syms,
  cgc_backend_copy_indirect_symbol,
  cgc_backend_hide_symbol,
  cgc_backend_fixup_symbol,
  cgc_backend_merge_symbol_attribute,
  cgc_backend_get_target_dtag,
  cgc_backend_ignore_undef_symbol,
  cgc_backend_emit_relocs,
  cgc_backend_count_relocs,
  cgc_backend_grok_prstatus,
  cgc_backend_grok_psinfo,
  cgc_backend_write_core_note,
  cgc_backend_lookup_section_flags_hook,
  cgc_backend_reloc_type_class,
  cgc_backend_discard_info,
  cgc_backend_ignore_discarded_relocs,
  cgc_backend_action_discarded,
  cgc_backend_eh_frame_address_size,
  cgc_backend_can_make_relative_eh_frame,
  cgc_backend_can_make_lsda_relative_eh_frame,
  cgc_backend_encode_eh_address,
  cgc_backend_write_section,
  cgc_backend_mips_irix_compat,
  cgc_backend_mips_rtype_to_howto,
  cgc_backend_ecoff_debug_swap,
  cgc_backend_bfd_from_remote_memory,
  cgc_backend_plt_sym_val,
  cgc_backend_common_definition,
  cgc_backend_common_section_index,
  cgc_backend_common_section,
  cgc_backend_merge_symbol,
  cgc_backend_hash_symbol,
  cgc_backend_is_function_type,
  cgc_backend_maybe_function_sym,
  cgc_backend_link_order_error_handler,
  cgc_backend_relplt_name,
  CGC_MACHINE_ALT1,
  CGC_MACHINE_ALT2,
  &cgc_backend_size_info,
  cgc_backend_special_sections,
  cgc_backend_got_header_size,
  cgc_backend_got_elt_size,
  cgc_backend_obj_attrs_vendor,
  cgc_backend_obj_attrs_section,
  cgc_backend_obj_attrs_arg_type,
  cgc_backend_obj_attrs_section_type,
  cgc_backend_obj_attrs_order,
  cgc_backend_obj_attrs_handle_unknown,
  cgc_backend_static_tls_alignment,
  cgc_backend_stack_align,
  cgc_backend_collect,
  cgc_backend_type_change_ok,
  cgc_backend_may_use_rel_p,
  cgc_backend_may_use_rela_p,
  cgc_backend_default_use_rela_p,
  cgc_backend_rela_plts_and_copies_p,
  cgc_backend_rela_normal,
  cgc_backend_sign_extend_vma,
  cgc_backend_want_got_plt,
  cgc_backend_plt_readonly,
  cgc_backend_want_plt_sym,
  cgc_backend_plt_not_loaded,
  cgc_backend_plt_alignment,
  cgc_backend_can_gc_sections,
  cgc_backend_can_refcount,
  cgc_backend_want_got_sym,
  cgc_backend_want_dynbss,
  cgc_backend_want_p_paddr_set_to_zero,
  cgc_backend_default_execstack
};

/* Forward declaration for use when initialising alternative_target field.  */
#ifdef TARGET_LITTLE_SYM
extern const bfd_target TARGET_LITTLE_SYM;
#endif

#ifdef TARGET_BIG_SYM
const bfd_target TARGET_BIG_SYM =
{
  /* name: identify kind of target */
  TARGET_BIG_NAME,

  /* flavour: general indication about file */
  bfd_target_cgc_flavour,

  /* byteorder: data is big endian */
  BFD_ENDIAN_BIG,

  /* header_byteorder: header is also big endian */
  BFD_ENDIAN_BIG,

  /* object_flags: mask of all file flags */
  (HAS_RELOC | EXEC_P | HAS_LINENO | HAS_DEBUG | HAS_SYMS | HAS_LOCALS
   | DYNAMIC | WP_TEXT | D_PAGED | BFD_COMPRESS | BFD_DECOMPRESS),

  /* section_flags: mask of all section flags */
  (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD | SEC_RELOC | SEC_READONLY
   | SEC_CODE | SEC_DATA | SEC_DEBUGGING | SEC_EXCLUDE | SEC_SORT_ENTRIES
   | SEC_SMALL_DATA | SEC_MERGE | SEC_STRINGS | SEC_GROUP),

   /* leading_symbol_char: is the first char of a user symbol
      predictable, and if so what is it */
  cgc_symbol_leading_char,

  /* ar_pad_char: pad character for filenames within an archive header
     FIXME:  this really has nothing to do with CGC, this is a characteristic
     of the archiver and/or os and should be independently tunable */
  '/',

  /* ar_max_namelen: maximum number of characters in an archive header
     FIXME:  this really has nothing to do with CGC, this is a characteristic
     of the archiver and should be independently tunable.  The System V ABI,
     Chapter 7 (Formats & Protocols), Archive section sets this as 15.  */
  15,

  cgc_match_priority,

  /* Routines to byte-swap various sized integers from the data sections */
  bfd_getb64, bfd_getb_signed_64, bfd_putb64,
    bfd_getb32, bfd_getb_signed_32, bfd_putb32,
    bfd_getb16, bfd_getb_signed_16, bfd_putb16,

  /* Routines to byte-swap various sized integers from the file headers */
  bfd_getb64, bfd_getb_signed_64, bfd_putb64,
    bfd_getb32, bfd_getb_signed_32, bfd_putb32,
    bfd_getb16, bfd_getb_signed_16, bfd_putb16,

  /* bfd_check_format: check the format of a file being read */
  { _bfd_dummy_target,		/* unknown format */
    bfd_cgcNN_object_p,		/* assembler/linker output (object file) */
    bfd_cgcNN_archive_p,	/* an archive */
    bfd_cgcNN_core_file_p	/* a core file */
  },

  /* bfd_set_format: set the format of a file being written */
  { bfd_false,
    bfd_cgcNN_mkobject,
    bfd_cgcNN_mkarchive,
    bfd_cgcNN_mkcorefile
  },

  /* bfd_write_contents: write cached information into a file being written */
  { bfd_false,
    bfd_cgcNN_write_object_contents,
    bfd_cgcNN_write_archive_contents,
    bfd_cgcNN_write_corefile_contents,
  },

  BFD_JUMP_TABLE_GENERIC (bfd_cgcNN),
  BFD_JUMP_TABLE_COPY (bfd_cgcNN),
  BFD_JUMP_TABLE_CORE (bfd_cgcNN),
#ifdef bfd_cgcNN_archive_functions
  BFD_JUMP_TABLE_ARCHIVE (bfd_cgcNN_archive),
#else
  BFD_JUMP_TABLE_ARCHIVE (_bfd_archive_coff),
#endif
  BFD_JUMP_TABLE_SYMBOLS (bfd_cgcNN),
  BFD_JUMP_TABLE_RELOCS (bfd_cgcNN),
  BFD_JUMP_TABLE_WRITE (bfd_cgcNN),
  BFD_JUMP_TABLE_LINK (bfd_cgcNN),
  BFD_JUMP_TABLE_DYNAMIC (bfd_cgcNN),

  /* Alternative endian target.  */
#ifdef TARGET_LITTLE_SYM
  & TARGET_LITTLE_SYM,
#else
  NULL,
#endif

  /* backend_data: */
  &cgcNN_bed
};
#endif

#ifdef TARGET_LITTLE_SYM
const bfd_target TARGET_LITTLE_SYM =
{
  /* name: identify kind of target */
  TARGET_LITTLE_NAME,

  /* flavour: general indication about file */
  bfd_target_cgc_flavour,

  /* byteorder: data is little endian */
  BFD_ENDIAN_LITTLE,

  /* header_byteorder: header is also little endian */
  BFD_ENDIAN_LITTLE,

  /* object_flags: mask of all file flags */
  (HAS_RELOC | EXEC_P | HAS_LINENO | HAS_DEBUG | HAS_SYMS | HAS_LOCALS
   | DYNAMIC | WP_TEXT | D_PAGED | BFD_COMPRESS | BFD_DECOMPRESS),

  /* section_flags: mask of all section flags */
  (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD | SEC_RELOC | SEC_READONLY
   | SEC_CODE | SEC_DATA | SEC_DEBUGGING | SEC_EXCLUDE | SEC_SORT_ENTRIES
   | SEC_SMALL_DATA | SEC_MERGE | SEC_STRINGS | SEC_GROUP),

   /* leading_symbol_char: is the first char of a user symbol
      predictable, and if so what is it */
  cgc_symbol_leading_char,

  /* ar_pad_char: pad character for filenames within an archive header
     FIXME:  this really has nothing to do with CGC, this is a characteristic
     of the archiver and/or os and should be independently tunable */
  '/',

  /* ar_max_namelen: maximum number of characters in an archive header
     FIXME:  this really has nothing to do with CGC, this is a characteristic
     of the archiver and should be independently tunable.  The System V ABI,
     Chapter 7 (Formats & Protocols), Archive section sets this as 15.  */
  15,

  cgc_match_priority,

  /* Routines to byte-swap various sized integers from the data sections */
  bfd_getl64, bfd_getl_signed_64, bfd_putl64,
    bfd_getl32, bfd_getl_signed_32, bfd_putl32,
    bfd_getl16, bfd_getl_signed_16, bfd_putl16,

  /* Routines to byte-swap various sized integers from the file headers */
  bfd_getl64, bfd_getl_signed_64, bfd_putl64,
    bfd_getl32, bfd_getl_signed_32, bfd_putl32,
    bfd_getl16, bfd_getl_signed_16, bfd_putl16,

  /* bfd_check_format: check the format of a file being read */
  { _bfd_dummy_target,		/* unknown format */
    bfd_cgcNN_object_p,		/* assembler/linker output (object file) */
    bfd_cgcNN_archive_p,	/* an archive */
    bfd_cgcNN_core_file_p	/* a core file */
  },

  /* bfd_set_format: set the format of a file being written */
  { bfd_false,
    bfd_cgcNN_mkobject,
    bfd_cgcNN_mkarchive,
    bfd_cgcNN_mkcorefile
  },

  /* bfd_write_contents: write cached information into a file being written */
  { bfd_false,
    bfd_cgcNN_write_object_contents,
    bfd_cgcNN_write_archive_contents,
    bfd_cgcNN_write_corefile_contents,
  },

  BFD_JUMP_TABLE_GENERIC (bfd_cgcNN),
  BFD_JUMP_TABLE_COPY (bfd_cgcNN),
  BFD_JUMP_TABLE_CORE (bfd_cgcNN),
#ifdef bfd_cgcNN_archive_functions
  BFD_JUMP_TABLE_ARCHIVE (bfd_cgcNN_archive),
#else
  BFD_JUMP_TABLE_ARCHIVE (_bfd_archive_coff),
#endif
  BFD_JUMP_TABLE_SYMBOLS (bfd_cgcNN),
  BFD_JUMP_TABLE_RELOCS (bfd_cgcNN),
  BFD_JUMP_TABLE_WRITE (bfd_cgcNN),
  BFD_JUMP_TABLE_LINK (bfd_cgcNN),
  BFD_JUMP_TABLE_DYNAMIC (bfd_cgcNN),

  /* Alternative endian target.  */
#ifdef TARGET_BIG_SYM
  & TARGET_BIG_SYM,
#else
  NULL,
#endif

  /* backend_data: */
  &cgcNN_bed
};
#endif
