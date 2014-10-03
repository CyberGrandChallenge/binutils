// cgccpp_internal.h -- internals for cgccpp   -*- C++ -*-

// Copyright 2006, 2007, Free Software Foundation, Inc.
// Written by Ian Lance Taylor <iant@google.com>.

// This file is part of cgccpp.
   
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2, or
// (at your option) any later version.

// In addition to the permissions in the GNU Library General Public
// License, the Free Software Foundation gives you unlimited
// permission to link the compiled version of this file into
// combinations with other programs, and to distribute those
// combinations without any restriction coming from the use of this
// file.  (The Library Public License restrictions do apply in other
// respects; for example, they cover modification of the file, and
/// distribution when not linked into a combined executable.)

// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.

// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
// 02110-1301, USA.

// This is included by cgccpp.h, the external interface, but holds
// information which we want to keep private.

#ifndef CGCCPP_INTERNAL_H
#define CGCCPP_INTERNAL_H

namespace cgccpp
{

namespace internal
{

// The CGC file header.

template<int size>
struct Ehdr_data
{
  unsigned char e_ident[EI_NIDENT];
  Cgc_Half e_type;
  Cgc_Half e_machine;
  Cgc_Word e_version;
  typename Cgc_types<size>::Cgc_Addr e_entry;
  typename Cgc_types<size>::Cgc_Off e_phoff;
  typename Cgc_types<size>::Cgc_Off e_shoff;
  Cgc_Word e_flags;
  Cgc_Half e_ehsize;
  Cgc_Half e_phentsize;
  Cgc_Half e_phnum;
  Cgc_Half e_shentsize;
  Cgc_Half e_shnum;
  Cgc_Half e_shstrndx;
};

// An CGC section header.

template<int size>
struct Shdr_data
{
  Cgc_Word sh_name;
  Cgc_Word sh_type;
  typename Cgc_types<size>::Cgc_WXword sh_flags;
  typename Cgc_types<size>::Cgc_Addr sh_addr;
  typename Cgc_types<size>::Cgc_Off sh_offset;
  typename Cgc_types<size>::Cgc_WXword sh_size;
  Cgc_Word sh_link;
  Cgc_Word sh_info;
  typename Cgc_types<size>::Cgc_WXword sh_addralign;
  typename Cgc_types<size>::Cgc_WXword sh_entsize;
};

// An CGC segment header.  We use template specialization for the
// 32-bit and 64-bit versions because the fields are in a different
// order.

template<int size>
struct Phdr_data;

template<>
struct Phdr_data<32>
{
  Cgc_Word p_type;
  Cgc_types<32>::Cgc_Off p_offset;
  Cgc_types<32>::Cgc_Addr p_vaddr;
  Cgc_types<32>::Cgc_Addr p_paddr;
  Cgc_Word p_filesz;
  Cgc_Word p_memsz;
  Cgc_Word p_flags;
  Cgc_Word p_align;
};

template<>
struct Phdr_data<64>
{
  Cgc_Word p_type;
  Cgc_Word p_flags;
  Cgc_types<64>::Cgc_Off p_offset;
  Cgc_types<64>::Cgc_Addr p_vaddr;
  Cgc_types<64>::Cgc_Addr p_paddr;
  Cgc_Xword p_filesz;
  Cgc_Xword p_memsz;
  Cgc_Xword p_align;
};

// An CGC symbol table entry.  We use template specialization for the
// 32-bit and 64-bit versions because the fields are in a different
// order.

template<int size>
struct Sym_data;

template<>
struct Sym_data<32>
{
  Cgc_Word st_name;
  Cgc_types<32>::Cgc_Addr st_value;
  Cgc_Word st_size;
  unsigned char st_info;
  unsigned char st_other;
  Cgc_Half st_shndx;
};

template<>
struct Sym_data<64>
{
  Cgc_Word st_name;
  unsigned char st_info;
  unsigned char st_other;
  Cgc_Half st_shndx;
  Cgc_types<64>::Cgc_Addr st_value;
  Cgc_Xword st_size;
};

// CGC relocation table entries.

template<int size>
struct Rel_data
{
  typename Cgc_types<size>::Cgc_Addr r_offset;
  typename Cgc_types<size>::Cgc_WXword r_info;
};

template<int size>
struct Rela_data
{
  typename Cgc_types<size>::Cgc_Addr r_offset;
  typename Cgc_types<size>::Cgc_WXword r_info;
  typename Cgc_types<size>::Cgc_Swxword r_addend;
};

// An entry in the CGC SHT_DYNAMIC section aka PT_DYNAMIC segment.

template<int size>
struct Dyn_data
{
  typename Cgc_types<size>::Cgc_Swxword d_tag;
  typename Cgc_types<size>::Cgc_WXword d_val;
};

// An entry in a SHT_GNU_verdef section.  This structure is the same
// in 32-bit and 64-bit CGC files.

struct Verdef_data
{
  // Version number of structure (VER_DEF_*).
  Cgc_Half vd_version;
  // Bit flags (VER_FLG_*).
  Cgc_Half vd_flags;
  // Version index.
  Cgc_Half vd_ndx;
  // Number of auxiliary Verdaux entries.
  Cgc_Half vd_cnt;
  // Hash of name.
  Cgc_Word vd_hash;
  // Byte offset to first Verdaux entry.
  Cgc_Word vd_aux;
  // Byte offset to next Verdef entry.
  Cgc_Word vd_next;
};

// An auxiliary entry in a SHT_GNU_verdef section.  This structure is
// the same in 32-bit and 64-bit CGC files.

struct Verdaux_data
{
  // Offset in string table of version name.
  Cgc_Word vda_name;
  // Byte offset to next Verdaux entry.
  Cgc_Word vda_next;
};

// An entry in a SHT_GNU_verneed section.  This structure is the same
// in 32-bit and 64-bit CGC files.

struct Verneed_data
{
  // Version number of structure (VER_NEED_*).
  Cgc_Half vn_version;
  // Number of auxiliary Vernaux entries.
  Cgc_Half vn_cnt;
  // Offset in string table of library name.
  Cgc_Word vn_file;
  // Byte offset to first Vernaux entry.
  Cgc_Word vn_aux;
  // Byt eoffset to next Verneed entry.
  Cgc_Word vn_next;
};

// An auxiliary entry in a SHT_GNU_verneed section.  This structure is
// the same in 32-bit and 64-bit CGC files.

struct Vernaux_data
{
  // Hash of dependency name.
  Cgc_Word vna_hash;
  // Bit flags (VER_FLG_*).
  Cgc_Half vna_flags;
  // Version index used in SHT_GNU_versym entries.
  Cgc_Half vna_other;
  // Offset in string table of version name.
  Cgc_Word vna_name;
  // Byte offset to next Vernaux entry.
  Cgc_Word vna_next;
};

} // End namespace internal.

} // End namespace cgccpp.

#endif // !defined(CGCCPP_INTERNAL_H)
