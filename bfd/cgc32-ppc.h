/* PowerPC-specific support for 64-bit CGC.
   Copyright 2003, 2005, 2007, 2009, 2012 Free Software Foundation, Inc.

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

enum ppc_cgc_plt_type
{
  PLT_UNSET,
  PLT_OLD,
  PLT_NEW,
  PLT_VXWORKS
};

int ppc_cgc_select_plt_layout (bfd *, struct bfd_link_info *,
			       enum ppc_cgc_plt_type, int);
asection *ppc_cgc_tls_setup (bfd *, struct bfd_link_info *, int);
bfd_boolean ppc_cgc_tls_optimize (bfd *, struct bfd_link_info *);
void ppc_cgc_set_sdata_syms (bfd *, struct bfd_link_info *);
extern bfd_boolean ppc_cgc_modify_segment_map (bfd *,
		           struct bfd_link_info * ATTRIBUTE_UNUSED);
extern bfd_boolean ppc_cgc_section_processing (bfd *, Cgc_Internal_Shdr *);
