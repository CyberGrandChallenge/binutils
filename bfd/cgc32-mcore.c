/* Motorola MCore specific support for 32-bit CGC
   Copyright 1994, 1995, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2007, 2011, 2012 Free Software Foundation, Inc.

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


/* This file is based on a preliminary RCE CGC ABI.  The
   information may not match the final RCE CGC ABI.   */

#include "sysdep.h"
#include "bfd.h"
#include "bfdlink.h"
#include "libbfd.h"
#include "cgc-bfd.h"
#include "cgc/mcore.h"
#include <assert.h>

/* RELA relocs are used here...  */

/* Function to set whether a module needs the -mrelocatable bit set.  */

static bfd_boolean
mcore_cgc_set_private_flags (bfd * abfd, flagword flags)
{
  BFD_ASSERT (! cgc_flags_init (abfd)
	      || cgc_cgcheader (abfd)->e_flags == flags);

  cgc_cgcheader (abfd)->e_flags = flags;
  cgc_flags_init (abfd) = TRUE;
  return TRUE;
}

/* Merge backend specific data from an object file to the output
   object file when linking.  */

static bfd_boolean
mcore_cgc_merge_private_bfd_data (bfd * ibfd, bfd * obfd)
{
  flagword old_flags;
  flagword new_flags;

  /* Check if we have the same endianness.  */
  if (! _bfd_generic_verify_endian_match (ibfd, obfd))
    return FALSE;

  if (   bfd_get_flavour (ibfd) != bfd_target_cgc_flavour
      || bfd_get_flavour (obfd) != bfd_target_cgc_flavour)
    return TRUE;

  new_flags = cgc_cgcheader (ibfd)->e_flags;
  old_flags = cgc_cgcheader (obfd)->e_flags;

  if (! cgc_flags_init (obfd))
    {
      	/* First call, no flags set.  */
      cgc_flags_init (obfd) = TRUE;
      cgc_cgcheader (obfd)->e_flags = new_flags;
    }
  else if (new_flags == old_flags)
    /* Compatible flags are OK.  */
    ;
  else
    {
      /* FIXME */
    }

  return TRUE;
}

/* Don't pretend we can deal with unsupported relocs.  */

static bfd_reloc_status_type
mcore_cgc_unsupported_reloc (bfd * abfd,
			     arelent * reloc_entry,
			     asymbol * symbol ATTRIBUTE_UNUSED,
			     void * data ATTRIBUTE_UNUSED,
			     asection * input_section ATTRIBUTE_UNUSED,
			     bfd * output_bfd ATTRIBUTE_UNUSED,
			     char ** error_message ATTRIBUTE_UNUSED)
{
  BFD_ASSERT (reloc_entry->howto != (reloc_howto_type *)0);

  _bfd_error_handler (_("%B: Relocation %s (%d) is not currently supported.\n"),
		      abfd,
		      reloc_entry->howto->name,
		      reloc_entry->howto->type);

  return bfd_reloc_notsupported;
}

static reloc_howto_type * mcore_cgc_howto_table [(int) R_MCORE_max];

static reloc_howto_type mcore_cgc_howto_raw[] =
{
  /* This reloc does nothing.  */
  HOWTO (R_MCORE_NONE,		/* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 FALSE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield,  /* complain_on_overflow */
	 NULL,                  /* special_function */
	 "R_MCORE_NONE",	/* name */
	 FALSE,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 FALSE),		/* pcrel_offset */

  /* A standard 32 bit relocation.  */
  HOWTO (R_MCORE_ADDR32,	/* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 FALSE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_cgc_generic_reloc,	/* special_function */
	 "ADDR32",		/* name *//* For compatibility with coff/pe port.  */
	 FALSE,			/* partial_inplace */
	 0x0,			/* src_mask */
	 0xffffffff,		/* dst_mask */
	 FALSE),		/* pcrel_offset */

  /* 8 bits + 2 zero bits; jmpi/jsri/lrw instructions.
     Should not appear in object files.  */
  HOWTO (R_MCORE_PCRELIMM8BY4,	/* type */
	 2,			/* rightshift */
	 1,			/* size (0 = byte, 1 = short, 2 = long) */
	 8,			/* bitsize */
	 TRUE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 mcore_cgc_unsupported_reloc,	/* special_function */
	 "R_MCORE_PCRELIMM8BY4",/* name */
	 FALSE,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 TRUE),			/* pcrel_offset */

  /* bsr/bt/bf/br instructions; 11 bits + 1 zero bit
     Span 2k instructions == 4k bytes.
     Only useful pieces at the relocated address are the opcode (5 bits) */
  HOWTO (R_MCORE_PCRELIMM11BY2,/* type */
	 1,			/* rightshift */
	 1,			/* size (0 = byte, 1 = short, 2 = long) */
	 11,			/* bitsize */
	 TRUE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 bfd_cgc_generic_reloc,	/* special_function */
	 "R_MCORE_PCRELIMM11BY2",/* name */
	 FALSE,			/* partial_inplace */
	 0x0,			/* src_mask */
	 0x7ff,			/* dst_mask */
	 TRUE),			/* pcrel_offset */

  /* 4 bits + 1 zero bit; 'loopt' instruction only; unsupported.  */
  HOWTO (R_MCORE_PCRELIMM4BY2,	/* type */
	 1,			/* rightshift */
	 1,			/* size (0 = byte, 1 = short, 2 = long) */
	 4,			/* bitsize */
	 TRUE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 mcore_cgc_unsupported_reloc,/* special_function */
	 "R_MCORE_PCRELIMM4BY2",/* name */
	 FALSE,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 TRUE),			/* pcrel_offset */

  /* 32-bit pc-relative. Eventually this will help support PIC code.  */
  HOWTO (R_MCORE_PCREL32,	/* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 TRUE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_cgc_generic_reloc,	/* special_function */
	 "R_MCORE_PCREL32",	/* name */
	 FALSE,			/* partial_inplace */
	 0x0,			/* src_mask */
	 0xffffffff,		/* dst_mask */
	 TRUE),			/* pcrel_offset */

  /* Like PCRELIMM11BY2, this relocation indicates that there is a
     'jsri' at the specified address. There is a separate relocation
     entry for the literal pool entry that it references, but we
     might be able to change the jsri to a bsr if the target turns out
     to be close enough [even though we won't reclaim the literal pool
     entry, we'll get some runtime efficiency back]. Note that this
     is a relocation that we are allowed to safely ignore.  */
  HOWTO (R_MCORE_PCRELJSR_IMM11BY2,/* type */
	 1,			/* rightshift */
	 1,			/* size (0 = byte, 1 = short, 2 = long) */
	 11,			/* bitsize */
	 TRUE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 bfd_cgc_generic_reloc,	/* special_function */
	 "R_MCORE_PCRELJSR_IMM11BY2", /* name */
	 FALSE,			/* partial_inplace */
	 0x0,			/* src_mask */
	 0x7ff,			/* dst_mask */
	 TRUE),			/* pcrel_offset */

  /* GNU extension to record C++ vtable hierarchy.  */
  HOWTO (R_MCORE_GNU_VTINHERIT, /* type */
         0,                     /* rightshift */
         2,                     /* size (0 = byte, 1 = short, 2 = long) */
         0,                     /* bitsize */
         FALSE,                 /* pc_relative */
         0,                     /* bitpos */
         complain_overflow_dont, /* complain_on_overflow */
         NULL,                  /* special_function */
         "R_MCORE_GNU_VTINHERIT", /* name */
         FALSE,                 /* partial_inplace */
         0,                     /* src_mask */
         0,                     /* dst_mask */
         FALSE),                /* pcrel_offset */

  /* GNU extension to record C++ vtable member usage.  */
  HOWTO (R_MCORE_GNU_VTENTRY,   /* type */
         0,                     /* rightshift */
         2,                     /* size (0 = byte, 1 = short, 2 = long) */
         0,                     /* bitsize */
         FALSE,                 /* pc_relative */
         0,                     /* bitpos */
         complain_overflow_dont,/* complain_on_overflow */
         _bfd_cgc_rel_vtable_reloc_fn,  /* special_function */
         "R_MCORE_GNU_VTENTRY", /* name */
         FALSE,                 /* partial_inplace */
         0,                     /* src_mask */
         0,                     /* dst_mask */
         FALSE),                /* pcrel_offset */

  HOWTO (R_MCORE_RELATIVE,      /* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 FALSE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 NULL,                  /* special_function */
	 "R_MCORE_RELATIVE",    /* name */
	 TRUE,			/* partial_inplace */
	 0xffffffff,		/* src_mask */
	 0xffffffff,		/* dst_mask */
	 FALSE)			/* pcrel_offset */
};

#ifndef NUM_ELEM
#define NUM_ELEM(a) (sizeof (a) / sizeof (a)[0])
#endif

/* Initialize the mcore_cgc_howto_table, so that linear accesses can be done.  */
static void
mcore_cgc_howto_init (void)
{
  unsigned int i;

  for (i = NUM_ELEM (mcore_cgc_howto_raw); i--;)
    {
      unsigned int type;

      type = mcore_cgc_howto_raw[i].type;

      BFD_ASSERT (type < NUM_ELEM (mcore_cgc_howto_table));

      mcore_cgc_howto_table [type] = & mcore_cgc_howto_raw [i];
    }
}

static reloc_howto_type *
mcore_cgc_reloc_type_lookup (bfd * abfd ATTRIBUTE_UNUSED,
			     bfd_reloc_code_real_type code)
{
  enum cgc_mcore_reloc_type mcore_reloc = R_MCORE_NONE;

  switch (code)
    {
    case BFD_RELOC_NONE:		     mcore_reloc = R_MCORE_NONE; break;
    case BFD_RELOC_32:			     mcore_reloc = R_MCORE_ADDR32; break;
    case BFD_RELOC_MCORE_PCREL_IMM8BY4:	     mcore_reloc = R_MCORE_PCRELIMM8BY4; break;
    case BFD_RELOC_MCORE_PCREL_IMM11BY2:     mcore_reloc = R_MCORE_PCRELIMM11BY2; break;
    case BFD_RELOC_MCORE_PCREL_IMM4BY2:	     mcore_reloc = R_MCORE_PCRELIMM4BY2; break;
    case BFD_RELOC_32_PCREL:		     mcore_reloc = R_MCORE_PCREL32; break;
    case BFD_RELOC_MCORE_PCREL_JSR_IMM11BY2: mcore_reloc = R_MCORE_PCRELJSR_IMM11BY2; break;
    case BFD_RELOC_VTABLE_INHERIT:           mcore_reloc = R_MCORE_GNU_VTINHERIT; break;
    case BFD_RELOC_VTABLE_ENTRY:             mcore_reloc = R_MCORE_GNU_VTENTRY; break;
    case BFD_RELOC_RVA:                      mcore_reloc = R_MCORE_RELATIVE; break;
    default:
      return NULL;
    }

  if (! mcore_cgc_howto_table [R_MCORE_PCRELIMM8BY4])
    /* Initialize howto table if needed.  */
    mcore_cgc_howto_init ();

  return mcore_cgc_howto_table [(int) mcore_reloc];
};

static reloc_howto_type *
mcore_cgc_reloc_name_lookup (bfd *abfd ATTRIBUTE_UNUSED,
			     const char *r_name)
{
  unsigned int i;

  for (i = 0;
       i < sizeof (mcore_cgc_howto_raw) / sizeof (mcore_cgc_howto_raw[0]);
       i++)
    if (mcore_cgc_howto_raw[i].name != NULL
	&& strcasecmp (mcore_cgc_howto_raw[i].name, r_name) == 0)
      return &mcore_cgc_howto_raw[i];

  return NULL;
}

/* Set the howto pointer for a RCE CGC reloc.  */

static void
mcore_cgc_info_to_howto (bfd * abfd ATTRIBUTE_UNUSED,
			 arelent * cache_ptr,
			 Cgc_Internal_Rela * dst)
{
  if (! mcore_cgc_howto_table [R_MCORE_PCRELIMM8BY4])
    /* Initialize howto table if needed.  */
    mcore_cgc_howto_init ();

  BFD_ASSERT (CGC32_R_TYPE (dst->r_info) < (unsigned int) R_MCORE_max);

  cache_ptr->howto = mcore_cgc_howto_table [CGC32_R_TYPE (dst->r_info)];
}

/* The RELOCATE_SECTION function is called by the CGC backend linker
   to handle the relocations for a section.

   The relocs are always passed as Rela structures; if the section
   actually uses Rel structures, the r_addend field will always be
   zero.

   This function is responsible for adjust the section contents as
   necessary, and (if using Rela relocs and generating a
   relocatable output file) adjusting the reloc addend as
   necessary.

   This function does not have to worry about setting the reloc
   address or the reloc symbol index.

   LOCAL_SYMS is a pointer to the swapped in local symbols.

   LOCAL_SECTIONS is an array giving the section in the input file
   corresponding to the st_shndx field of each local symbol.

   The global hash table entry for the global symbols can be found
   via cgc_sym_hashes (input_bfd).

   When generating relocatable output, this function must handle
   STB_LOCAL/STT_SECTION symbols specially.  The output symbol is
   going to be the section symbol corresponding to the output
   section, which means that the addend must be adjusted
   accordingly.  */

static bfd_boolean
mcore_cgc_relocate_section (bfd * output_bfd,
			    struct bfd_link_info * info,
			    bfd * input_bfd,
			    asection * input_section,
			    bfd_byte * contents,
			    Cgc_Internal_Rela * relocs,
			    Cgc_Internal_Sym * local_syms,
			    asection ** local_sections)
{
  Cgc_Internal_Shdr * symtab_hdr = & cgc_tdata (input_bfd)->symtab_hdr;
  struct cgc_link_hash_entry ** sym_hashes = cgc_sym_hashes (input_bfd);
  Cgc_Internal_Rela * rel = relocs;
  Cgc_Internal_Rela * relend = relocs + input_section->reloc_count;
  bfd_boolean ret = TRUE;

#ifdef DEBUG
  _bfd_error_handler
    ("mcore_cgc_relocate_section called for %B section %A, %ld relocations%s",
     input_bfd,
     input_section,
     (long) input_section->reloc_count,
     (info->relocatable) ? " (relocatable)" : "");
#endif

  if (! mcore_cgc_howto_table [R_MCORE_PCRELIMM8BY4])	/* Initialize howto table if needed */
    mcore_cgc_howto_init ();

  for (; rel < relend; rel++)
    {
      enum cgc_mcore_reloc_type    r_type = (enum cgc_mcore_reloc_type) CGC32_R_TYPE (rel->r_info);
      bfd_vma                      offset = rel->r_offset;
      bfd_vma                      addend = rel->r_addend;
      bfd_reloc_status_type        r = bfd_reloc_other;
      asection *                   sec = NULL;
      reloc_howto_type *           howto;
      bfd_vma                      relocation;
      Cgc_Internal_Sym *           sym = NULL;
      unsigned long                r_symndx;
      struct cgc_link_hash_entry * h = NULL;
      unsigned short               oldinst = 0;

      /* Unknown relocation handling.  */
      if ((unsigned) r_type >= (unsigned) R_MCORE_max
	  || ! mcore_cgc_howto_table [(int)r_type])
	{
	  _bfd_error_handler (_("%B: Unknown relocation type %d\n"),
			      input_bfd, (int) r_type);

	  bfd_set_error (bfd_error_bad_value);
	  ret = FALSE;
	  continue;
	}

      howto = mcore_cgc_howto_table [(int) r_type];
      r_symndx = CGC32_R_SYM (rel->r_info);

      /* Complain about known relocation that are not yet supported.  */
      if (howto->special_function == mcore_cgc_unsupported_reloc)
	{
	  _bfd_error_handler (_("%B: Relocation %s (%d) is not currently supported.\n"),
			      input_bfd,
			      howto->name,
			      (int)r_type);

	  bfd_set_error (bfd_error_bad_value);
	  ret = FALSE;
	  continue;
	}

      if (r_symndx < symtab_hdr->sh_info)
	{
	  sym = local_syms + r_symndx;
	  sec = local_sections [r_symndx];
	  relocation = _bfd_cgc_rela_local_sym (output_bfd, sym, &sec, rel);
	  addend = rel->r_addend;
	}
      else
	{
	  bfd_boolean unresolved_reloc, warned;

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
	default:
	  break;

	case R_MCORE_PCRELJSR_IMM11BY2:
	  oldinst = bfd_get_16 (input_bfd, contents + offset);
#define	MCORE_INST_BSR	0xF800
	  bfd_put_16 (input_bfd, (bfd_vma) MCORE_INST_BSR, contents + offset);
	  break;
	}

#ifdef DEBUG
      fprintf (stderr, "\ttype = %s (%d), symbol index = %ld, offset = %ld, addend = %ld\n",
	       howto->name, r_type, r_symndx, (long) offset, (long) addend);
#endif

      r = _bfd_final_link_relocate
	(howto, input_bfd, input_section, contents, offset, relocation, addend);

      if (r != bfd_reloc_ok && r_type == R_MCORE_PCRELJSR_IMM11BY2)
	{
	  /* Wasn't ok, back it out and give up.  */
	  bfd_put_16 (input_bfd, (bfd_vma) oldinst, contents + offset);
	  r = bfd_reloc_ok;
	}

      if (r != bfd_reloc_ok)
	{
	  ret = FALSE;

	  switch (r)
	    {
	    default:
	      break;

	    case bfd_reloc_overflow:
	      {
		const char * name;

		if (h != NULL)
		  name = NULL;
		else
		  {
		    name = bfd_cgc_string_from_cgc_section
		      (input_bfd, symtab_hdr->sh_link, sym->st_name);

		    if (name == NULL)
		      break;

		    if (* name == '\0')
		      name = bfd_section_name (input_bfd, sec);
		  }

		(*info->callbacks->reloc_overflow)
		  (info, (h ? &h->root : NULL), name, howto->name,
		   (bfd_vma) 0, input_bfd, input_section, offset);
	      }
	      break;
	    }
	}
    }

#ifdef DEBUG
  fprintf (stderr, "\n");
#endif

  return ret;
}

/* Return the section that should be marked against GC for a given
   relocation.  */

static asection *
mcore_cgc_gc_mark_hook (asection *sec,
			struct bfd_link_info *info,
			Cgc_Internal_Rela *rel,
			struct cgc_link_hash_entry *h,
			Cgc_Internal_Sym *sym)
{
  if (h != NULL)
    switch (CGC32_R_TYPE (rel->r_info))
      {
      case R_MCORE_GNU_VTINHERIT:
      case R_MCORE_GNU_VTENTRY:
	return NULL;
      }

  return _bfd_cgc_gc_mark_hook (sec, info, rel, h, sym);
}

/* Update the got entry reference counts for the section being removed.  */

static bfd_boolean
mcore_cgc_gc_sweep_hook (bfd * abfd ATTRIBUTE_UNUSED,
			 struct bfd_link_info * info ATTRIBUTE_UNUSED,
			 asection * sec ATTRIBUTE_UNUSED,
			 const Cgc_Internal_Rela * relocs ATTRIBUTE_UNUSED)
{
  return TRUE;
}

/* Look through the relocs for a section during the first phase.
   Since we don't do .gots or .plts, we just need to consider the
   virtual table relocs for gc.  */

static bfd_boolean
mcore_cgc_check_relocs (bfd * abfd,
			struct bfd_link_info * info,
			asection * sec,
			const Cgc_Internal_Rela * relocs)
{
  Cgc_Internal_Shdr * symtab_hdr;
  struct cgc_link_hash_entry ** sym_hashes;
  const Cgc_Internal_Rela * rel;
  const Cgc_Internal_Rela * rel_end;

  if (info->relocatable)
    return TRUE;

  symtab_hdr = & cgc_tdata (abfd)->symtab_hdr;
  sym_hashes = cgc_sym_hashes (abfd);

  rel_end = relocs + sec->reloc_count;

  for (rel = relocs; rel < rel_end; rel++)
    {
      struct cgc_link_hash_entry * h;
      unsigned long r_symndx;

      r_symndx = CGC32_R_SYM (rel->r_info);

      if (r_symndx < symtab_hdr->sh_info)
        h = NULL;
      else
	{
	  h = sym_hashes [r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct cgc_link_hash_entry *) h->root.u.i.link;

	  /* PR15323, ref flags aren't set for references in the same
	     object.  */
	  h->root.non_ir_ref = 1;
	}

      switch (CGC32_R_TYPE (rel->r_info))
        {
        /* This relocation describes the C++ object vtable hierarchy.
           Reconstruct it for later use during GC.  */
        case R_MCORE_GNU_VTINHERIT:
          if (!bfd_cgc_gc_record_vtinherit (abfd, sec, h, rel->r_offset))
            return FALSE;
          break;

        /* This relocation describes which C++ vtable entries are actually
           used.  Record for later use during GC.  */
        case R_MCORE_GNU_VTENTRY:
          BFD_ASSERT (h != NULL);
          if (h != NULL
              && !bfd_cgc_gc_record_vtentry (abfd, sec, h, rel->r_addend))
            return FALSE;
          break;
        }
    }

  return TRUE;
}

static const struct bfd_cgc_special_section mcore_cgc_special_sections[]=
{
  { STRING_COMMA_LEN (".ctors"), -2, SHT_PROGBITS, SHF_ALLOC + SHF_WRITE },
  { STRING_COMMA_LEN (".dtors"), -2, SHT_PROGBITS, SHF_ALLOC + SHF_WRITE },
  { NULL,                     0,  0, 0,            0 }
};

#define TARGET_BIG_SYM		bfd_cgc32_mcore_big_vec
#define TARGET_BIG_NAME		"cgc32-mcore-big"
#define TARGET_LITTLE_SYM       bfd_cgc32_mcore_little_vec
#define TARGET_LITTLE_NAME      "cgc32-mcore-little"

#define CGC_ARCH		bfd_arch_mcore
#define CGC_MACHINE_CODE	EM_MCORE
#define CGC_MAXPAGESIZE		0x1000		/* 4k, if we ever have 'em */
#define cgc_info_to_howto	mcore_cgc_info_to_howto
#define cgc_info_to_howto_rel	NULL

#define bfd_cgc32_bfd_merge_private_bfd_data	mcore_cgc_merge_private_bfd_data
#define bfd_cgc32_bfd_set_private_flags		mcore_cgc_set_private_flags
#define bfd_cgc32_bfd_reloc_type_lookup		mcore_cgc_reloc_type_lookup
#define bfd_cgc32_bfd_reloc_name_lookup	mcore_cgc_reloc_name_lookup
#define cgc_backend_relocate_section		mcore_cgc_relocate_section
#define cgc_backend_gc_mark_hook		mcore_cgc_gc_mark_hook
#define cgc_backend_gc_sweep_hook		mcore_cgc_gc_sweep_hook
#define cgc_backend_check_relocs                mcore_cgc_check_relocs
#define cgc_backend_special_sections		mcore_cgc_special_sections

#define cgc_backend_can_gc_sections		1
#define cgc_backend_rela_normal			1

#include "cgc32-target.h"
