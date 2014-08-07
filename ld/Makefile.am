## Process this file with automake to generate Makefile.in
#
#   Copyright 2012 Free Software Foundation
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING3.  If not see
# <http://www.gnu.org/licenses/>.
#

AUTOMAKE_OPTIONS = dejagnu no-texinfo.tex no-dist foreign
ACLOCAL_AMFLAGS = -I .. -I ../config -I ../bfd
TEXINFO_TEX = ../texinfo/texinfo.tex

SUBDIRS = po

tooldir = $(exec_prefix)/$(target_alias)

YACC = `if [ -f ../bison/bison ]; then echo ../bison/bison -y -L$(srcdir)/../bison/; else echo @YACC@; fi`
YFLAGS = -d
LEX = `if [ -f ../flex/flex ]; then echo ../flex/flex; else echo @LEX@; fi`

# Automake 1.10+ disables lex and yacc output file regeneration if
# maintainer mode is disabled.  Avoid this.
am__skiplex =
am__skipyacc =

WARN_CFLAGS = @WARN_CFLAGS@
NO_WERROR = @NO_WERROR@
AM_CFLAGS = $(WARN_CFLAGS)

# Conditionally enable the plugin interface.
if ENABLE_PLUGINS
PLUGIN_C = plugin.c
PLUGIN_H = plugin.h
PLUGIN_OBJECT = plugin.@OBJEXT@
PLUGIN_CFLAGS = -DENABLE_PLUGINS
else
PLUGIN_C =
PLUGIN_H =
PLUGIN_OBJECT =
PLUGIN_CFLAGS =
endif

# We put the scripts in the directory $(scriptdir)/ldscripts.
# We can't put the scripts in $(datadir) because the SEARCH_DIR
# directives need to be different for native and cross linkers.
scriptdir = $(tooldir)/lib

EMUL = @EMUL@
EMULATION_OFILES = @EMULATION_OFILES@
EMUL_EXTRA_OFILES = @EMUL_EXTRA_OFILES@

# Search path to override the default search path for -lfoo libraries.
# If LIB_PATH is empty, the ones in the script (if any) are left alone.
# (The default is usually /lib:/usr/lib:/usr/local/lib, unless building
# a cross-linker, in which case the default is empty.  See genscripts.sh.)
# Otherwise, they are replaced with the ones given in LIB_PATH,
# which may have the form: LIB_PATH=/lib:/usr/local/lib.  This can be set
# when the linker is configured via the --with-lib-path configure switch.
LIB_PATH = @LIB_PATH@

BASEDIR = $(srcdir)/..
BFDDIR = $(BASEDIR)/bfd
INCDIR	= $(BASEDIR)/include

# What version of the manual to build
DOCVER = gen

# Options to extract the man page from ld.texinfo
MANCONF = -Dman

TEXI2POD = perl $(BASEDIR)/etc/texi2pod.pl $(AM_MAKEINFOFLAGS)

POD2MAN = pod2man --center="GNU Development Tools" \
	--release="binutils-$(VERSION)" --section=1

#stuff for self hosting (can be overridden in config file).
HOSTING_CRT0 = @HOSTING_CRT0@
HOSTING_SCRT0 = @HOSTING_SCRT0@
HOSTING_LIBS = @HOSTING_LIBS@
HOSTING_EMU = -m $(EMUL)

# Setup the testing framework, if you have one
EXPECT = expect
RUNTEST = runtest
RUNTESTFLAGS =

CC_FOR_TARGET = ` \
  if [ -f $$r/../gcc/xgcc ] ; then \
    if [ -f $$r/../newlib/Makefile ] ; then \
      echo $$r/../gcc/xgcc -B$$r/../gcc/ -idirafter $$r/../newlib/targ-include -idirafter $${srcroot}/../newlib/libc/include -nostdinc; \
    else \
      echo $$r/../gcc/xgcc -B$$r/../gcc/; \
    fi; \
  else \
    if [ "@host@" = "@target@" ] ; then \
      echo $(CC); \
    else \
      echo gcc | sed '$(transform)'; \
    fi; \
  fi`

CXX_FOR_TARGET = ` \
  if [ -f $$r/../gcc/g++ ] ; then \
    if [ -f $$r/../newlib/Makefile ] ; then \
      echo $$r/../gcc/g++ -B$$r/../gcc/ -idirafter $$r/../newlib/targ-include -idirafter $${srcroot}/../newlib/libc/include -nostdinc; \
    else \
      echo $$r/../gcc/g++ -B$$r/../gcc/; \
    fi; \
  else \
    if [ "@host@" = "@target@" ] ; then \
      echo $(CXX); \
    else \
      echo g++ | sed '$(transform)'; \
    fi; \
  fi`

transform = s/^ld-new$$/$(installed_linker)/;@program_transform_name@
bin_PROGRAMS = ld-new
info_TEXINFOS = ld.texinfo
ld_TEXINFOS = configdoc.texi
noinst_TEXINFOS = ldint.texinfo
man_MANS = ld.1

AM_MAKEINFOFLAGS = -I $(srcdir) -I $(BFDDIR)/doc -I ../bfd/doc \
		   -I $(top_srcdir)/../libiberty
TEXI2DVI = texi2dvi -I $(srcdir) -I $(BFDDIR)/doc -I ../bfd/doc \
		    -I $(top_srcdir)/../libiberty

AM_CPPFLAGS = -I. -I$(srcdir) -I../bfd -I$(BFDDIR) -I$(INCDIR) \
	@INCINTL@ $(HDEFINES) $(CFLAGS) $(PLUGIN_CFLAGS) \
	-DLOCALEDIR="\"$(datadir)/locale\""

BFDLIB = ../bfd/libbfd.la
LIBIBERTY = ../libiberty/libiberty.a

ALL_EMULATION_SOURCES = \
	eaix5ppc.c \
	eaix5rs6.c \
	eaixppc.c \
	eaixrs6.c \
	ealpha.c \
	ealphavms.c \
	earccgc.c \
	earm_epoc_pe.c \
	earm_wince_pe.c \
	earmaoutb.c \
	earmaoutl.c \
	earmcoff.c \
	earmcgc.c \
	earmcgc_fbsd.c \
	earmcgc_linux.c \
	earmcgc_linux_eabi.c \
	earmcgc_nacl.c \
	earmcgc_nbsd.c \
	earmcgc_vxworks.c \
	earmcgcb.c \
	earmcgcb_linux.c \
	earmcgcb_linux_eabi.c \
	earmcgcb_nacl.c \
	earmcgcb_nbsd.c \
	earmnbsd.c \
	earmnto.c \
	earmpe.c \
	earmsymbian.c \
	eavr1.c \
	eavr2.c \
	eavr25.c \
	eavr3.c \
	eavr31.c \
	eavr35.c \
	eavr4.c \
	eavr5.c \
	eavr51.c \
	eavr6.c \
	eavrxmega1.c \
	eavrxmega2.c \
	eavrxmega3.c \
	eavrxmega4.c \
	eavrxmega5.c \
	eavrxmega6.c \
	eavrxmega7.c \
	ecoff_i860.c \
	ecoff_sparc.c \
	ecrisaout.c \
	ecriself.c \
	ecrislinux.c \
	ed10vcgc.c \
	ed30v_e.c \
	ed30v_o.c \
	ed30vcgc.c \
	edelta68.c \
	ecgc32_dlx.c \
	ecgc32_i860.c \
	ecgc32_i960.c \
	ecgc32_sparc.c \
	ecgc32_sparc_sol2.c \
	ecgc32_sparc_vxworks.c \
	ecgc32_spu.c \
	ecgc32_tic6x_be.c \
	ecgc32_tic6x_le.c \
	ecgc32_tic6x_linux_be.c \
	ecgc32_tic6x_linux_le.c \
	ecgc32_tic6x_cgc_be.c \
	ecgc32_tic6x_cgc_le.c \
	ecgc32am33lin.c \
	ecgc32bfin.c \
	ecgc32bfinfd.c \
	ecgc32cr16.c \
	ecgc32cr16c.c \
	ecgc32crx.c \
	ecgc32epiphany.c \
	ecgc32epiphany_4x4.c \
	ecgc32fr30.c \
	ecgc32frv.c \
	ecgc32frvfd.c \
	ecgc32i370.c \
	ecgc32ip2k.c \
	ecgc32iq10.c \
	ecgc32iq2000.c \
	ecgc32lm32.c \
	ecgc32lm32fd.c \
	ecgc32lppc.c \
	ecgc32lppclinux.c \
	ecgc32lppcnto.c \
	ecgc32lppcsim.c \
	ecgc32m32c.c \
	ecgc32mb_linux.c \
	ecgc32mcore.c \
	ecgc32mep.c \
	ecgc32metag.c \
	ecgc32microblazeel.c \
	ecgc32microblaze.c \
	ecgc32moxie.c \
	ecgc32mt.c \
	ecgc32openrisc.c \
	ecgc32ppc.c \
	ecgc32ppc_fbsd.c \
	ecgc32ppclinux.c \
	ecgc32ppcnto.c \
	ecgc32ppcsim.c \
	ecgc32ppcvxworks.c \
	ecgc32ppcwindiss.c \
	ecgc32rl78.c \
	ecgc32rx.c \
	ecgc32tilegx.c \
	ecgc32tilegx_be.c \
	ecgc32tilepro.c \
	ecgc32vax.c \
	ecgc32xc16x.c \
	ecgc32xc16xl.c \
	ecgc32xc16xs.c \
	ecgc32xstormy16.c \
	ecgc32xtensa.c \
	ecgc_i386.c \
	ecgc_i386_be.c \
	ecgc_i386_chaos.c \
	ecgc_i386_fbsd.c \
	ecgc_i386_ldso.c \
	ecgc_i386_nacl.c \
	ecgc_i386_sol2.c \
	ecgc_i386_vxworks.c \
	ecgc_s390.c \
	egld960.c \
	egld960coff.c \
	eh8300.c \
	eh8300cgc.c \
	eh8300h.c \
	eh8300hcgc.c \
	eh8300hn.c \
	eh8300hncgc.c \
	eh8300s.c \
	eh8300self.c \
	eh8300sn.c \
	eh8300sncgc.c \
	eh8300sx.c \
	eh8300sxcgc.c \
	eh8300sxn.c \
	eh8300sxncgc.c \
	eh8500.c \
	eh8500b.c \
	eh8500c.c \
	eh8500m.c \
	eh8500s.c \
	ehp300bsd.c \
	ehp3hpux.c \
	ehppacgc.c \
	ehppalinux.c \
	ehppanbsd.c \
	ehppaobsd.c \
	ei386aout.c \
	ei386beos.c \
	ei386bsd.c \
	ei386coff.c \
	ei386go32.c \
	ei386linux.c \
	ei386lynx.c \
	ei386mach.c \
	ei386moss.c \
	ei386msdos.c \
	ei386nbsd.c \
	ei386nto.c \
	ei386nw.c \
	ei386pe.c \
	ei386pe_posix.c \
	ei386pep.c \
	elnk960.c \
	em32rcgc.c \
	em32rcgc_linux.c \
	em32rlcgc.c \
	em32rlcgc_linux.c \
	em68hc11cgc.c \
	em68hc11cgcb.c \
	em68hc12cgc.c \
	em68hc12cgcb.c \
	em68k4knbsd.c \
	em68kaout.c \
	em68kaux.c \
	em68kcoff.c \
	em68kcgc.c \
	em68kcgcnbsd.c \
	em68klinux.c \
	em68knbsd.c \
	em68kpsos.c \
	em88kbcs.c \
	emcorepe.c \
	emn10200.c \
	emn10300.c \
	emsp430x110.c \
	emsp430x1101.c \
	emsp430x1111.c \
	emsp430x112.c \
	emsp430x1121.c \
	emsp430x1122.c \
	emsp430x1132.c \
	emsp430x122.c \
	emsp430x1222.c \
	emsp430x123.c \
	emsp430x1232.c \
	emsp430x133.c \
	emsp430x1331.c \
	emsp430x135.c \
	emsp430x1351.c \
	emsp430x147.c \
	emsp430x148.c \
	emsp430x149.c \
	emsp430x155.c \
	emsp430x156.c \
	emsp430x157.c \
	emsp430x1610.c \
	emsp430x1611.c \
	emsp430x1612.c \
	emsp430x167.c \
	emsp430x168.c \
	emsp430x169.c \
	emsp430x2101.c \
	emsp430x2111.c \
	emsp430x2121.c \
	emsp430x2131.c \
	emsp430x311.c \
	emsp430x312.c \
	emsp430x313.c \
	emsp430x314.c \
	emsp430x315.c \
	emsp430x323.c \
	emsp430x325.c \
	emsp430x336.c \
	emsp430x337.c \
	emsp430x412.c \
	emsp430x413.c \
	emsp430x415.c \
	emsp430x417.c \
	emsp430x435.c \
	emsp430x436.c \
	emsp430x437.c \
	emsp430x447.c \
	emsp430x448.c \
	emsp430x449.c \
	emsp430xE423.c \
	emsp430xE425.c \
	emsp430xE427.c \
	emsp430xG437.c \
	emsp430xG438.c \
	emsp430xG439.c \
	emsp430xW423.c \
	emsp430xW425.c \
	emsp430xW427.c \
	emsp430X.c \
	enews.c \
	ens32knbsd.c \
	eor32.c \
	eor32cgc.c \
	epc532macha.c \
	epdp11.c \
	epjcgc.c \
	epjlcgc.c \
	eppclynx.c \
	eppcmacos.c \
	eppcnw.c \
	eppcpe.c \
	eriscix.c \
	escore3_cgc.c \
	escore7_cgc.c \
	esh.c \
	eshcgc.c \
	eshcgc32.c \
	eshcgc32_linux.c \
	eshcgc32_nbsd.c \
	eshcgc_fd.c \
	eshcgc_linux.c \
	eshcgc_nbsd.c \
	eshcgc_nto.c \
	eshcgc_uclinux.c \
	eshcgc_vxworks.c \
	eshl.c \
	eshlcgc.c \
	eshlcgc32.c \
	eshlcgc32_linux.c \
	eshlcgc32_nbsd.c \
	eshlcgc_fd.c \
	eshlcgc_linux.c \
	eshlcgc_nbsd.c \
	eshlcgc_nto.c \
	eshlcgc_vxworks.c \
	eshlsymbian.c \
	eshpe.c \
	esparcaout.c \
	esparclinux.c \
	esparcnbsd.c \
	est2000.c \
	esun3.c \
	esun4.c \
	etic30aout.c \
	etic30coff.c \
	etic3xcoff.c \
	etic3xcoff_onchip.c \
	etic4xcoff.c \
	etic54xcoff.c \
	etic80coff.c \
	ev850.c \
	ev850_rh850.c \
	evanilla.c \
	evax.c \
	evaxnbsd.c \
	evsta.c \
	ew65.c \
	exgatecgc.c \
	ez80.c \
	ez8001.c \
	ez8002.c

ALL_EMULATIONS = $(ALL_EMULATION_SOURCES:.c=.@OBJEXT@)

ALL_64_EMULATION_SOURCES = \
	eaarch64cgc.c \
	eaarch64cgc32.c \
	eaarch64cgcb.c \
	eaarch64cgc32b.c \
	eaarch64linux.c \
	eaarch64linuxb.c \
	eaarch64linux32.c \
	eaarch64linux32b.c \
	ecgc32_x86_64.c \
	ecgc32_x86_64_nacl.c \
	ecgc32b4300.c \
	ecgc32bmip.c \
	ecgc32bmipn32.c \
	ecgc32bsmip.c \
	ecgc32btsmip.c \
	ecgc32btsmip_fbsd.c \
	ecgc32btsmipn32.c \
	ecgc32btsmipn32_fbsd.c \
	ecgc32ebmip.c \
	ecgc32ebmipvxworks.c \
	ecgc32elmip.c \
	ecgc32elmipvxworks.c \
	ecgc32l4300.c \
	ecgc32lmip.c \
	ecgc32lr5900.c \
	ecgc32lr5900n32.c \
	ecgc32lsmip.c \
	ecgc32ltsmip.c \
	ecgc32ltsmip_fbsd.c \
	ecgc32ltsmipn32.c \
	ecgc32ltsmipn32_fbsd.c \
	ecgc32mipswindiss.c \
	ecgc64_aix.c \
	ecgc64_ia64.c \
	ecgc64_ia64_fbsd.c \
	ecgc64_ia64_vms.c \
	ecgc64_s390.c \
	ecgc64_sparc.c \
	ecgc64_sparc_fbsd.c \
	ecgc64_sparc_sol2.c \
	ecgc64alpha.c \
	ecgc64alpha_fbsd.c \
	ecgc64alpha_nbsd.c \
	ecgc64bmip.c \
	ecgc64btsmip.c \
	ecgc64btsmip_fbsd.c \
	ecgc64hppa.c \
	ecgc64lppc.c \
	ecgc64ltsmip.c \
	ecgc64ltsmip_fbsd.c \
	ecgc64mmix.c \
	ecgc64ppc.c \
	ecgc64ppc_fbsd.c \
	ecgc64rdos.c \
	ecgc64tilegx.c \
	ecgc64tilegx_be.c \
	ecgc_l1om.c \
	ecgc_l1om_fbsd.c \
	ecgc_k1om.c \
	ecgc_k1om_fbsd.c \
	ecgc_x86_64.c \
	ecgc_x86_64_fbsd.c \
	ecgc_x86_64_nacl.c \
	ecgc_x86_64_sol2.c \
	ehppa64linux.c \
	emmo.c \
	eshcgc64.c \
	eshcgc64_nbsd.c \
	eshlcgc64.c \
	eshlcgc64_nbsd.c

ALL_64_EMULATIONS = $(ALL_64_EMULATION_SOURCES:.c=.@OBJEXT@)

ALL_EMUL_EXTRA_OFILES = \
	deffilep.@OBJEXT@ \
	pe-dll.@OBJEXT@ \
	pep-dll.@OBJEXT@

CFILES = ldctor.c ldemul.c ldexp.c ldfile.c ldlang.c \
	ldmain.c ldmisc.c ldver.c ldwrite.c lexsup.c \
	mri.c ldcref.c pe-dll.c pep-dll.c ldlex-wrapper.c \
	$(PLUGIN_C)

HFILES = ld.h ldctor.h ldemul.h ldexp.h ldfile.h \
	ldlang.h ldlex.h ldmain.h ldmisc.h ldver.h \
	ldwrite.h mri.h deffile.h pe-dll.h pep-dll.h \
	cgc-hints-local.h $(PLUGIN_H)

GENERATED_CFILES = ldgram.c ldlex.c deffilep.c
GENERATED_HFILES = ldgram.h ldemul-list.h deffilep.h

# Require an early dependency on the generated headers, as the dependency
# tracking will not cause them to be built beforehand.
BUILT_SOURCES = $(GENERATED_HFILES)

OFILES = ldgram.@OBJEXT@ ldlex-wrapper.@OBJEXT@ lexsup.@OBJEXT@ ldlang.@OBJEXT@ \
	mri.@OBJEXT@ ldctor.@OBJEXT@ ldmain.@OBJEXT@ $(PLUGIN_OBJECT) \
	ldwrite.@OBJEXT@ ldexp.@OBJEXT@  ldemul.@OBJEXT@ ldver.@OBJEXT@ ldmisc.@OBJEXT@ \
	ldfile.@OBJEXT@ ldcref.@OBJEXT@ ${EMULATION_OFILES} ${EMUL_EXTRA_OFILES}

STAGESTUFF = *.@OBJEXT@ ldscripts/* e*.c

# Disable -Werror, if it has been enabled, since old versions of bison/
# yacc will produce working code which contain compile time warnings.
ldgram.@OBJEXT@: ldgram.c
if am__fastdepCC
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `test -f ldgram.c || echo $(srcdir)/`ldgram.c $(NO_WERROR)
	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
else
if AMDEP
	source='ldgram.c' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(COMPILE) -c `test -f ldgram.c || echo $(srcdir)/`ldgram.c $(NO_WERROR)
endif

ldlex-wrapper.@OBJEXT@: ldlex-wrapper.c ldlex.c
if am__fastdepCC
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $(srcdir)/ldlex-wrapper.c $(NO_WERROR)
	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
else
if AMDEP
	source='ldlex-wrapper.c' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(COMPILE) -c $(srcdir)/ldlex-wrapper.c $(NO_WERROR)
endif

deffilep.@OBJEXT@: deffilep.c
if am__fastdepCC
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `test -f deffilep.c || echo $(srcdir)/`deffilep.c $(NO_WERROR)
	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
else
if AMDEP
	source='deffilep.c' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(COMPILE) -c `test -f deffilep.c || echo $(srcdir)/`deffilep.c $(NO_WERROR)
endif

# At the moment this is just a list of those emulation template files
# that contain internationalised strings.
EMULATION_FILES = emultempl/pe.em emultempl/armcoff.em

POTFILES = $(CFILES) $(HFILES) $(EMULATION_FILES)

po/POTFILES.in: @MAINT@ Makefile
	for f in $(POTFILES); do echo $$f; done | LC_ALL=C sort > tmp \
	  && mv tmp $(srcdir)/po/POTFILES.in

ldmain.@OBJEXT@: ldmain.c config.status
if am__fastdepCC
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ \
	  -DDEFAULT_EMULATION='"$(EMUL)"' \
	  -DBINDIR='"$(bindir)"' -DTOOLBINDIR='"$(tooldir)/bin"' \
	  -DTARGET='"@target@"' @TARGET_SYSTEM_ROOT_DEFINE@ \
	  $(srcdir)/ldmain.c
	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
else
if AMDEP
	source='ldmain.c' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(COMPILE) -c -DDEFAULT_EMULATION='"$(EMUL)"' \
	  -DBINDIR='"$(bindir)"' -DTOOLBINDIR='"$(tooldir)/bin"' \
	  -DTARGET='"@target@"' @TARGET_SYSTEM_ROOT_DEFINE@ \
	  $(srcdir)/ldmain.c
endif

ldfile.@OBJEXT@: ldfile.c config.status
if am__fastdepCC
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ \
	-DSCRIPTDIR='"$(scriptdir)"' -DBINDIR='"$(bindir)"' -DTOOLBINDIR='"$(tooldir)/bin"' \
	 $(srcdir)/ldfile.c
	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
else
if AMDEP
	source='ldfile.c' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(COMPILE) -c -DSCRIPTDIR='"$(scriptdir)"' -DBINDIR='"$(bindir)"' \
	  -DTOOLBINDIR='"$(tooldir)/bin"' \
	  $(srcdir)/ldfile.c
endif

ecgc32_spu.@OBJEXT@: ecgc32_spu.c
if am__fastdepCC
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ \
	  -DEMBEDSPU="\"`echo embedspu | sed '$(transform)'`\"" ecgc32_spu.c
	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
else
if AMDEP
	source='ecgc32_spu.c' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(COMPILE) -c -DEMBEDSPU="\"`echo embedspu | sed '$(transform)'`\"" \
	  ecgc32_spu.c
endif

ldemul-list.h: Makefile
	(echo "/* This file is automatically generated.  DO NOT EDIT! */";\
	for f in `echo " " ${EMULATION_OFILES} "" \
	 | sed -e 's/ e/ ld/g' -e 's/ ld/ /g' -e 's/[.]o//g'`; do \
	    echo "extern ld_emulation_xfer_type ld_$${f}_emulation;"; \
	done;\
	echo "";\
	echo "#define EMULATION_LIST \\";\
	for f in `echo " " ${EMULATION_OFILES} "" \
	 | sed -e 's/ e/ ld/g' -e 's/ ld/ /g' -e 's/[.]o//g'`; do \
	    echo "  &ld_$${f}_emulation, \\"; \
	done;\
	echo "  0") >ldemul-tmp.h
	mv ldemul-tmp.h ldemul-list.h

stringify.sed: ${srcdir}/emultempl/$(STRINGIFY)
	  cp ${srcdir}/emultempl/$(STRINGIFY) stringify.sed

# These all start with e so 'make clean' can find them.

GENSCRIPTS = LIB_PATH='${LIB_PATH}' $(SHELL) $(srcdir)/genscripts.sh "${srcdir}" "${libdir}" "${prefix}" "${exec_prefix}" @host@ @target@ @target_alias@ "@EMULATION_LIBPATH@" "@NATIVE_LIB_DIRS@" @use_sysroot@ @enable_initfini_array@
GEN_DEPENDS = $(srcdir)/genscripts.sh stringify.sed
CGC_DEPS = $(srcdir)/emultempl/cgc32.em $(srcdir)/emultempl/cgc-generic.em $(srcdir)/scripttempl/DWARF.sc
CGC_GEN_DEPS = $(srcdir)/emultempl/generic.em $(srcdir)/emultempl/cgc-generic.em $(srcdir)/emultempl/gencgc.em $(srcdir)/scripttempl/DWARF.sc

@TDIRS@

eaix5ppc.c: $(srcdir)/emulparams/aix5ppc.sh \
  $(srcdir)/emultempl/aix.em $(srcdir)/scripttempl/aix.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aix5ppc "$(tdir_aixppc)"
eaix5rs6.c: $(srcdir)/emulparams/aix5rs6.sh \
  $(srcdir)/emultempl/aix.em $(srcdir)/scripttempl/aix.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aix5rs6 "$(tdir_aixrs6)"
eaixppc.c: $(srcdir)/emulparams/aixppc.sh \
  $(srcdir)/emultempl/aix.em $(srcdir)/scripttempl/aix.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aixppc "$(tdir_aixppc)"
eaixrs6.c: $(srcdir)/emulparams/aixrs6.sh \
  $(srcdir)/emultempl/aix.em $(srcdir)/scripttempl/aix.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aixrs6 "$(tdir_aixrs6)"
ealpha.c: $(srcdir)/emulparams/alpha.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/alpha.sc ${GEN_DEPENDS}
	${GENSCRIPTS} alpha "$(tdir_alpha)"
ealphavms.c: $(srcdir)/emulparams/alphavms.sh \
  $(srcdir)/emultempl/vms.em $(srcdir)/scripttempl/alphavms.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} alphavms "$(tdir_alphavms)"
earccgc.c: $(srcdir)/emulparams/arccgc.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} arccgc "$(tdir_arccgc)"
earm_epoc_pe.c: $(srcdir)/emulparams/arm_epoc_pe.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/epocpe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} arm_epoc_pe "$(tdir_armpe)"
earm_wince_pe.c: $(srcdir)/emulparams/arm_wince_pe.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/pe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} arm_wince_pe "$(tdir_armpe)"
earmaoutb.c:	$(srcdir)/emulparams/armaoutb.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/armaout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armaoutb "$(tdir_armaoutb)"
earmaoutl.c:	$(srcdir)/emulparams/armaoutl.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/armaout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armaoutl "$(tdir_armaoutl)"
earmcoff.c:	$(srcdir)/emulparams/armcoff.sh \
  $(srcdir)/emultempl/armcoff.em $(srcdir)/scripttempl/armcoff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcoff "$(tdir_armcoff)"
earmcgc.c: $(srcdir)/emulparams/armcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgc "$(tdir_armcgc)"
earmcgc_fbsd.c: $(srcdir)/emulparams/armcgc_fbsd.sh \
  $(srcdir)/emulparams/armcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgc_fbsd "$(tdir_armcgc_fbsd)"
earmcgc_linux.c: $(srcdir)/emulparams/armcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgc_linux "$(tdir_armcgc_linux)"
earmcgc_linux_eabi.c: $(srcdir)/emulparams/armcgc_linux_eabi.sh \
  $(srcdir)/emulparams/armcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgc_linux_eabi "$(tdir_armcgc_linux_abi)"
earmcgc_nacl.c: $(srcdir)/emulparams/armcgc_nacl.sh \
  $(srcdir)/emulparams/armcgc_linux_eabi.sh \
  $(srcdir)/emulparams/armcgc_linux.sh \
  $(srcdir)/emulparams/cgc_nacl.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgc_nacl "$(tdir_armcgc_nacl)"
earmcgc_nbsd.c: $(srcdir)/emulparams/armcgc_nbsd.sh \
  $(srcdir)/emulparams/armcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgc_nbsd "$(tdir_armcgc_nbsd)"
earmcgc_vxworks.c: $(srcdir)/emulparams/armcgc_vxworks.sh \
  $(srcdir)/emulparams/vxworks.sh $(srcdir)/emulparams/armcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/vxworks.em \
  $(srcdir)/emultempl/armcgc.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} armcgc_vxworks "$(tdir_armcgc)"
earmcgcb.c: $(srcdir)/emulparams/armcgcb.sh $(srcdir)/emulparams/armcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgcb "$(tdir_armcgcb)"
earmcgcb_linux.c: $(srcdir)/emulparams/armcgcb_linux.sh \
  $(srcdir)/emulparams/armcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgcb_linux "$(tdir_armcgcb_linux)"
earmcgcb_linux_eabi.c: $(srcdir)/emulparams/armcgcb_linux_eabi.sh \
  $(srcdir)/emulparams/armcgc_linux_eabi.sh \
  $(srcdir)/emulparams/armcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgcb_linux_eabi "$(tdir_armcgcb_linux_abi)"
earmcgcb_nacl.c: $(srcdir)/emulparams/armcgcb_nacl.sh \
  $(srcdir)/emulparams/armcgc_nacl.sh \
  $(srcdir)/emulparams/armcgc_linux_eabi.sh \
  $(srcdir)/emulparams/armcgc_linux.sh \
  $(srcdir)/emulparams/cgc_nacl.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgcb_nacl "$(tdir_armcgcb_nacl)"
earmcgcb_nbsd.c: $(srcdir)/emulparams/armcgcb_nbsd.sh \
  $(srcdir)/emulparams/armcgc_nbsd.sh \
  $(srcdir)/emulparams/armcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armcgcb_nbsd "$(tdir_armcgcb_nbsd)"
earmnbsd.c:	$(srcdir)/emulparams/armnbsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armnbsd "$(tdir_armnbsd)"
earmnto.c: $(srcdir)/emulparams/armnto.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/armcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armnto "$(tdir_armnto)"
earmpe.c: $(srcdir)/emulparams/armpe.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/pe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} armpe "$(tdir_armpe)"
earmsymbian.c: $(srcdir)/emulparams/armsymbian.sh \
  $(srcdir)/emulparams/armcgc.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/armcgc.em $(srcdir)/scripttempl/armbpabi.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} armsymbian "$(tdir_armcgc)"
eavr1.c: $(srcdir)/emulparams/avr1.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr1 "$(tdir_avr2)"
eavr2.c: $(srcdir)/emulparams/avr2.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr2 "$(tdir_avr2)"
eavr25.c: $(srcdir)/emulparams/avr25.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr25 "$(tdir_avr2)"
eavr3.c: $(srcdir)/emulparams/avr3.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr3 "$(tdir_avr2)"
eavr31.c: $(srcdir)/emulparams/avr31.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr31 "$(tdir_avr2)"
eavr35.c: $(srcdir)/emulparams/avr35.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr35 "$(tdir_avr2)"
eavr4.c: $(srcdir)/emulparams/avr4.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr4 "$(tdir_avr2)"
eavr5.c: $(srcdir)/emulparams/avr5.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr5 "$(tdir_avr2)"
eavr51.c: $(srcdir)/emulparams/avr51.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr51 "$(tdir_avr2)"
eavr6.c: $(srcdir)/emulparams/avr6.sh $(srcdir)/emultempl/avrcgc.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avr6 "$(tdir_avr2)"
eavrxmega1.c: $(srcdir)/emulparams/avrxmega1.sh \
  $(srcdir)/emultempl/avrcgc.em $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avrxmega1 "$(tdir_avr2)"
eavrxmega2.c: $(srcdir)/emulparams/avrxmega2.sh \
  $(srcdir)/emultempl/avrcgc.em $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avrxmega2 "$(tdir_avr2)"
eavrxmega3.c: $(srcdir)/emulparams/avrxmega3.sh \
  $(srcdir)/emultempl/avrcgc.em $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avrxmega3 "$(tdir_avr2)"
eavrxmega4.c: $(srcdir)/emulparams/avrxmega4.sh \
  $(srcdir)/emultempl/avrcgc.em $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avrxmega4 "$(tdir_avr2)"
eavrxmega5.c: $(srcdir)/emulparams/avrxmega5.sh \
  $(srcdir)/emultempl/avrcgc.em $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avrxmega5 "$(tdir_avr2)"
eavrxmega6.c: $(srcdir)/emulparams/avrxmega6.sh \
  $(srcdir)/emultempl/avrcgc.em $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avrxmega6 "$(tdir_avr2)"
eavrxmega7.c: $(srcdir)/emulparams/avrxmega7.sh \
  $(srcdir)/emultempl/avrcgc.em $(CGC_DEPS) $(srcdir)/scripttempl/avr.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} avrxmega7 "$(tdir_avr2)"
ecoff_i860.c: $(srcdir)/emulparams/coff_i860.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/i860coff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} coff_i860 "$(tdir_coff_i860)"
ecoff_sparc.c: $(srcdir)/emulparams/coff_sparc.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/sparccoff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} coff_sparc "$(tdir_coff_sparc)"
ecrisaout.c: $(srcdir)/emulparams/crisaout.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/crisaout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} crisaout "$(tdir_cris)"
ecriself.c: $(srcdir)/emulparams/criself.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} criself "$(tdir_cris)"
ecrislinux.c: $(srcdir)/emulparams/crislinux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} crislinux "$(tdir_cris)"
ed10vcgc.c: $(srcdir)/emulparams/d10vcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgcd10v.sc ${GEN_DEPENDS}
	${GENSCRIPTS} d10vcgc "$(tdir_d10v)"
ed30v_e.c: $(srcdir)/emulparams/d30v_e.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgcd30v.sc ${GEN_DEPENDS}
	${GENSCRIPTS} d30v_e "$(tdir_d30v)"
ed30v_o.c: $(srcdir)/emulparams/d30v_o.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgcd30v.sc ${GEN_DEPENDS}
	${GENSCRIPTS} d30v_o "$(tdir_d30v)"
ed30vcgc.c: $(srcdir)/emulparams/d30vcgc.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgcd30v.sc ${GEN_DEPENDS}
	${GENSCRIPTS} d30vcgc "$(tdir_d30v)"
edelta68.c: $(srcdir)/emulparams/delta68.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/delta68.sc ${GEN_DEPENDS}
	${GENSCRIPTS} delta68 "$(tdir_delta68)"
ecgc32_dlx.c: $(srcdir)/emulparams/cgc32_dlx.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/dlx.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_dlx "$(tdir_cgc32_dlx)"
ecgc32_i860.c: $(srcdir)/emulparams/cgc32_i860.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_i860 "$(tdir_cgc32_i860)"
ecgc32_i960.c: $(srcdir)/emulparams/cgc32_i960.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_i960 "$(tdir_cgc32_i960)"
ecgc32_sparc.c: $(srcdir)/emulparams/cgc32_sparc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_sparc "$(tdir_cgc32_sparc)"
ecgc32_sparc_sol2.c: $(srcdir)/emulparams/cgc32_sparc_sol2.sh \
  $(srcdir)/emulparams/cgc32_sparc.sh \
  $(srcdir)/emulparams/solaris2.sh \
  $(srcdir)/emultempl/solaris2.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_sparc_sol2 "$(tdir_cgc32_sparc_sol2)"
ecgc32_sparc_vxworks.c: $(srcdir)/emulparams/cgc32_sparc_vxworks.sh \
  $(srcdir)/emulparams/vxworks.sh $(srcdir)/emulparams/cgc32_sparc.sh \
  $(srcdir)/emultempl/vxworks.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_sparc_vxworks "$(tdir_cgc32_sparc_vxworks)"
ecgc32_spu.c: $(srcdir)/emulparams/cgc32_spu.sh $(srcdir)/emultempl/spucgc.em \
  $(srcdir)/emultempl/spu_ovl.@OBJEXT@_c $(srcdir)/emultempl/spu_icache.@OBJEXT@_c \
  ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_spu "$(tdir_cgc32_spu)"
$(srcdir)/emultempl/spu_ovl.@OBJEXT@_c: @MAINT@ $(srcdir)/emultempl/spu_ovl.S
	if ../gas/as-new --version \
		| grep 'target.*spu' >/dev/null 2>/dev/null; then \
	  cpp -DOVLY_IRQ_SAVE $(srcdir)/emultempl/spu_ovl.S spu_ovl.s; \
	  ../gas/as-new -o spu_ovl.@OBJEXT@ spu_ovl.s; \
	  ../binutils/bin2c <spu_ovl.@OBJEXT@ >$@; \
	fi
$(srcdir)/emultempl/spu_icache.@OBJEXT@_c: @MAINT@ $(srcdir)/emultempl/spu_icache.S
	if ../gas/as-new --version \
		| grep 'target.*spu' >/dev/null 2>/dev/null; then \
	  cpp -DOVLY_IRQ_SAVE $(srcdir)/emultempl/spu_icache.S spu_icache.s; \
	  ../gas/as-new -o spu_icache.@OBJEXT@ spu_icache.s; \
	  ../binutils/bin2c <spu_icache.@OBJEXT@ >$@; \
	fi
ecgc32_tic6x_be.c: $(srcdir)/emulparams/cgc32_tic6x_be.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc $(srcdir)/emultempl/tic6xdsbt.em \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_tic6x_be "$(tdir_cgc32_tic6x_be)"
ecgc32_tic6x_cgc_be.c: $(srcdir)/emulparams/cgc32_tic6x_cgc_be.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc  $(srcdir)/emultempl/tic6xdsbt.em \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_tic6x_cgc_be "$(tdir_cgc32_tic6x_cgc_be)"
ecgc32_tic6x_cgc_le.c: $(srcdir)/emulparams/cgc32_tic6x_cgc_le.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc  $(srcdir)/emultempl/tic6xdsbt.em \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_tic6x_cgc_le "$(tdir_cgc32_tic6x_cgc_le)"
ecgc32_tic6x_le.c: $(srcdir)/emulparams/cgc32_tic6x_le.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc $(srcdir)/emultempl/tic6xdsbt.em \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_tic6x_le "$(tdir_cgc32_tic6x_le)"
ecgc32_tic6x_linux_be.c: $(srcdir)/emulparams/cgc32_tic6x_linux_be.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc  $(srcdir)/emultempl/tic6xdsbt.em \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_tic6x_linux_be "$(tdir_cgc32_tic6x_linux_be)"
ecgc32_tic6x_linux_le.c: $(srcdir)/emulparams/cgc32_tic6x_linux_le.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc  $(srcdir)/emultempl/tic6xdsbt.em \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_tic6x_linux_le "$(tdir_cgc32_tic6x_linux_le)"
ecgc32am33lin.c: $(srcdir)/emulparams/cgc32am33lin.sh \
  $(srcdir)/emulparams/cgc32am33lin.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32am33lin "$(tdir_cgc32am33lin)"
ecgc32b4300.c: $(srcdir)/emulparams/cgc32b4300.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32b4300 "$(tdir_cgc32b4300)"
ecgc32bfin.c: $(srcdir)/emulparams/bfin.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/bfin.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32bfin "$(tdir_cgc32bfin)" bfin
ecgc32bfinfd.c: $(srcdir)/emulparams/cgc32bfinfd.sh \
  $(srcdir)/emulparams/bfin.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/bfin.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32bfinfd "$(tdir_cgc32bfinfd)" cgc32bfinfd
ecgc32bmip.c: $(srcdir)/emulparams/cgc32bmip.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32bmip "$(tdir_cgc32bmip)"
ecgc32bmipn32.c: $(srcdir)/emulparams/cgc32bmipn32.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/irix.em $(srcdir)/emultempl/mipself.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32bmipn32 "$(tdir_cgc32bmipn32)"
ecgc32bsmip.c: $(srcdir)/emulparams/cgc32bsmip.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(CGC_DEPS) $(srcdir)/emultempl/irix.em \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32bsmip "$(tdir_cgc32bsmip)"
ecgc32btsmip.c: $(srcdir)/emulparams/cgc32btsmip.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32btsmip "$(tdir_cgc32btsmip)"
ecgc32btsmip_fbsd.c: $(srcdir)/emulparams/cgc32btsmip_fbsd.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32btsmip_fbsd "$(tdir_cgc32btsmip_fbsd)"
ecgc32btsmipn32.c: $(srcdir)/emulparams/cgc32btsmipn32.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32btsmipn32 "$(tdir_cgc32btsmipn32)"
ecgc32btsmipn32_fbsd.c: $(srcdir)/emulparams/cgc32btsmipn32_fbsd.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32btsmipn32_fbsd "$(tdir_cgc32btsmipn32_fbsd)"
ecgc32cr16.c: $(srcdir)/emulparams/cgc32cr16.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/cr16cgc.em \
  $(srcdir)/scripttempl/cgc32cr16.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32cr16 "$(tdir_cgc32crx)"
ecgc32cr16c.c: $(srcdir)/emulparams/cgc32cr16c.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc32cr16c.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32cr16c "$(tdir_cgc32cr16c)"
ecgc32crx.c: $(srcdir)/emulparams/cgc32crx.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/crxcgc.em \
  $(srcdir)/scripttempl/cgc32crx.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32crx "$(tdir_cgc32crx)"
ecgc32ebmip.c: $(srcdir)/emulparams/cgc32ebmip.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ebmip "$(tdir_cgc32ebmip)"
ecgc32ebmipvxworks.c: $(srcdir)/emulparams/cgc32ebmipvxworks.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(srcdir)/emulparams/vxworks.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/generic.em $(srcdir)/emultempl/mipself.em \
  $(srcdir)/emultempl/vxworks.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ebmipvxworks "$(tdir_cgc32ebmipvxworks)"
ecgc32elmip.c: $(srcdir)/emulparams/cgc32elmip.sh \
  $(srcdir)/emulparams/cgc32lmip.sh $(srcdir)/emulparams/cgc32bmip.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32elmip "$(tdir_cgc32elmip)"
ecgc32elmipvxworks.c: $(srcdir)/emulparams/cgc32elmipvxworks.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(srcdir)/emulparams/vxworks.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/generic.em $(srcdir)/emultempl/mipself.em \
  $(srcdir)/emultempl/vxworks.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32elmipvxworks "$(tdir_cgc32elmipvxworks)"
ecgc32lr5900.c: $(srcdir)/emulparams/cgc32lr5900.sh \
  $(srcdir)/emulparams/cgc32bmip.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lr5900 "$(tdir_cgc32lr5900)"
ecgc32lr5900n32.c: $(srcdir)/emulparams/cgc32lr5900n32.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lr5900n32 "$(tdir_cgc32lr5900n32)"
ecgc32epiphany.c: $(srcdir)/emulparams/cgc32epiphany.sh \
  $(CGC_DEPS) ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32epiphany "$(tdir_epiphany)"
ecgc32epiphany_4x4.c: $(srcdir)/emulparams/cgc32epiphany_4x4.sh \
  $(srcdir)/emultempl/cgc32.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/epiphany_4x4.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32epiphany_4x4 "$(tdir_epiphany_4x4)"
ecgc32fr30.c: $(srcdir)/emulparams/cgc32fr30.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32fr30 "$(tdir_fr30)"
ecgc32frv.c: $(srcdir)/emulparams/cgc32frv.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32frv "$(tdir_frv)"
ecgc32frvfd.c: $(srcdir)/emulparams/cgc32frvfd.sh \
  $(srcdir)/emulparams/cgc32frv.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32frvfd "$(tdir_frv)"
ecgc32i370.c: $(srcdir)/emulparams/cgc32i370.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgci370.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32i370 "$(tdir_cgc32i370)"
ecgc32ip2k.c: $(srcdir)/emulparams/cgc32ip2k.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ip2k "$(tdir_ip2k)"
ecgc32iq10.c: $(srcdir)/emulparams/cgc32iq10.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/iq2000.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32iq10 "$(tdir_iq10)"
ecgc32iq2000.c: $(srcdir)/emulparams/cgc32iq2000.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/iq2000.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32iq2000 "$(tdir_iq2000)"
ecgc32l4300.c: $(srcdir)/emulparams/cgc32l4300.sh \
  $(srcdir)/emulparams/cgc32b4300.sh $(srcdir)/emulparams/cgc32bmip.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32l4300 "$(tdir_cgc32l4300)"
ecgc32lm32.c: $(srcdir)/emulparams/cgc32lm32.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lm32 "$(tdir_cgc32lm32)"
ecgc32lm32fd.c: $(srcdir)/emulparams/cgc32lm32fd.sh \
  $(srcdir)/emulparams/cgc32lm32.sh $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lm32fd "$(tdir_cgc32lm32fd)"
ecgc32lmip.c: $(srcdir)/emulparams/cgc32lmip.sh \
  $(srcdir)/emulparams/cgc32bmip.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lmip "$(tdir_cgc32lmip)"
ecgc32lppc.c: $(srcdir)/emulparams/cgc32lppc.sh \
  $(srcdir)/emulparams/cgc32ppccommon.sh \
  $(srcdir)/emulparams/cgc32ppc.sh $(srcdir)/emultempl/ppc32cgc.em \
  ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lppc "$(tdir_cgc32lppc)"
ecgc32lppclinux.c: $(srcdir)/emulparams/cgc32lppclinux.sh \
  $(srcdir)/emulparams/cgc32lppc.sh $(srcdir)/emulparams/cgc32ppc.sh \
  $(srcdir)/emulparams/cgc32ppccommon.sh $(srcdir)/emultempl/ppc32cgc.em \
  ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lppclinux "$(tdir_cgc32lppclinux)"
ecgc32lppcnto.c: $(srcdir)/emulparams/cgc32lppcnto.sh \
  $(srcdir)/emulparams/cgc32ppc.sh $(srcdir)/emulparams/cgc32ppccommon.sh \
  $(srcdir)/emultempl/ppc32cgc.em $(CGC_DEPS) \
  ldemul-list.h \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lppcnto "$(tdir_cgc32lppcnto)"
ecgc32lppcsim.c: $(srcdir)/emulparams/cgc32lppcsim.sh \
  $(srcdir)/emulparams/cgc32lppc.sh $(srcdir)/emulparams/cgc32ppc.sh \
  $(srcdir)/emulparams/cgc32ppccommon.sh $(srcdir)/emultempl/ppc32cgc.em \
  ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lppcsim "$(tdir_cgc32lppcsim)"
ecgc32lsmip.c: $(srcdir)/emulparams/cgc32lsmip.sh \
  $(srcdir)/emulparams/cgc32lmip.sh $(srcdir)/emulparams/cgc32bmip.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32lsmip "$(tdir_cgc32lsmip)"
ecgc32ltsmip.c: $(srcdir)/emulparams/cgc32ltsmip.sh \
  $(srcdir)/emulparams/cgc32btsmip.sh $(srcdir)/emulparams/cgc32bmip.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ltsmip "$(tdir_cgc32ltsmip)"
ecgc32ltsmip_fbsd.c: $(srcdir)/emulparams/cgc32ltsmip_fbsd.sh \
  $(srcdir)/emulparams/cgc32btsmip.sh $(srcdir)/emulparams/cgc32bmip.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ltsmip_fbsd "$(tdir_cgc32ltsmip_fbsd)"
ecgc32ltsmipn32.c: $(srcdir)/emulparams/cgc32ltsmipn32.sh \
  $(srcdir)/emulparams/cgc32btsmipn32.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ltsmipn32 "$(tdir_cgc32ltsmipn32)"
ecgc32ltsmipn32_fbsd.c: $(srcdir)/emulparams/cgc32ltsmipn32_fbsd.sh \
  $(srcdir)/emulparams/cgc32btsmipn32.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ltsmipn32_fbsd "$(tdir_cgc32ltsmipn32_fbsd)"
ecgc32m32c.c: $(srcdir)/emulparams/cgc32m32c.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32m32c "$(tdir_m32c)"
ecgc32mbel_linux.c: $(srcdir)/emulparams/cgc32mbel_linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32mbel_linux "$(tdir_microblazeel)"
ecgc32mb_linux.c: $(srcdir)/emulparams/cgc32mb_linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32mb_linux "$(tdir_microblaze)"
ecgc32mcore.c: $(srcdir)/emulparams/cgc32mcore.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32mcore "$(tdir_mcore)"
ecgc32mep.c: $(srcdir)/emulparams/cgc32mep.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/mep.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32mep "$(tdir_mep)"
ecgc32metag.c: $(srcdir)/emulparams/cgc32metag.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/metagcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32metag "$(tdir_metag)"
ecgc32microblazeel.c: $(srcdir)/emulparams/cgc32microblazeel.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgcmicroblaze.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32microblazeel "$(tdir_microblazeel)"
ecgc32microblaze.c: $(srcdir)/emulparams/cgc32microblaze.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgcmicroblaze.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32microblaze "$(tdir_microblaze)"
ecgc32mipswindiss.c: $(srcdir)/emulparams/cgc32mipswindiss.sh $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32mipswindiss "$(tdir_cgc32mipswindiss)"
ecgc32moxie.c: $(srcdir)/emulparams/cgc32moxie.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32moxie "$(tdir_moxie)"
ecgc32mt.c: $(srcdir)/emulparams/cgc32mt.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32mt "$(tdir_mt)"
ecgc32openrisc.c: $(srcdir)/emulparams/cgc32openrisc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32openrisc "$(tdir_openrisc)"
ecgc32ppc.c: $(srcdir)/emulparams/cgc32ppc.sh \
  $(srcdir)/emulparams/cgc32ppccommon.sh $(srcdir)/emultempl/ppc32cgc.em \
  ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ppc "$(tdir_cgc32ppc)"
ecgc32ppc_fbsd.c: $(srcdir)/emulparams/cgc32ppc_fbsd.sh \
  $(srcdir)/emulparams/cgc32ppc.sh $(srcdir)/emulparams/cgc32ppccommon.sh \
  $(srcdir)/emultempl/ppc32cgc.em $(CGC_DEPS) \
  ldemul-list.h \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ppc_fbsd "$(tdir_cgc32ppc_fbsd)"
ecgc32ppclinux.c: $(srcdir)/emulparams/cgc32ppclinux.sh \
  $(srcdir)/emulparams/cgc32ppc.sh $(srcdir)/emulparams/cgc32ppccommon.sh \
  $(srcdir)/emultempl/ppc32cgc.em $(CGC_DEPS) \
  ldemul-list.h \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ppclinux "$(tdir_cgc32ppclinux)"
ecgc32ppcnto.c: $(srcdir)/emulparams/cgc32ppcnto.sh \
  $(srcdir)/emulparams/cgc32ppc.sh $(srcdir)/emulparams/cgc32ppccommon.sh \
  $(srcdir)/emultempl/ppc32cgc.em $(CGC_DEPS) \
  ldemul-list.h \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ppcnto "$(tdir_cgc32ppcnto)"
ecgc32ppcsim.c: $(srcdir)/emulparams/cgc32ppcsim.sh \
  $(srcdir)/emulparams/cgc32ppc.sh $(srcdir)/emulparams/cgc32ppccommon.sh \
  $(srcdir)/emultempl/ppc32cgc.em $(CGC_DEPS) \
  ldemul-list.h \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ppcsim "$(tdir_cgc32ppcsim)"
ecgc32ppcvxworks.c: $(srcdir)/emulparams/cgc32ppcvxworks.sh \
  $(srcdir)/emulparams/cgc32ppccommon.sh $(srcdir)/emulparams/vxworks.sh \
  $(srcdir)/emultempl/vxworks.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ppcvxworks "$(tdir_cgc32ppcvxworks)"
ecgc32ppcwindiss.c: $(srcdir)/emulparams/cgc32ppcwindiss.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32ppcwindiss "$(tdir_cgc32ppcwindiss)"
ecgc32rl78.c: $(srcdir)/emulparams/cgc32rl78.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32rl78 "$(tdir_cgc32rl78)"
ecgc32rx.c: $(srcdir)/emulparams/cgc32rx.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32rx "$(tdir_cgc32rx)"
ecgc32tilegx.c: $(srcdir)/emulparams/cgc32tilegx.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32tilegx "$(tdir_tilegx)"
ecgc32tilegx_be.c: $(srcdir)/emulparams/cgc32tilegx_be.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32tilegx_be "$(tdir_tilegx_be)"
ecgc32tilepro.c: $(srcdir)/emulparams/cgc32tilepro.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32tilepro "$(tdir_tilepro)"
ecgc32vax.c: $(srcdir)/emulparams/cgc32vax.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32vax "$(tdir_cgc32vax)"
ecgc32xc16x.c: $(srcdir)/emulparams/cgc32xc16x.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32xc16x "$(tdir_xc16x)"
ecgc32xc16xl.c: $(srcdir)/emulparams/cgc32xc16xl.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32xc16xl "$(tdir_xc16xl)"
ecgc32xc16xs.c: $(srcdir)/emulparams/cgc32xc16xs.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32xc16xs "$(tdir_xc16xs)"
ecgc32xstormy16.c: $(srcdir)/emulparams/cgc32xstormy16.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/xstormy16.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32xstormy16 "$(tdir_xstormy16)"
ecgc32xtensa.c: $(srcdir)/emulparams/cgc32xtensa.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/xtensacgc.em $(INCDIR)/xtensa-config.h \
  $(BFDDIR)/cgc-bfd.h $(BFDDIR)/libbfd.h $(INCDIR)/cgc/xtensa.h \
  $(srcdir)/scripttempl/cgcxtensa.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32xtensa "$(tdir_cgc32xtensa)"
ecgc_i386.c: $(srcdir)/emulparams/cgc_i386.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386 "$(tdir_cgc_i386)"
ecgc_i386_be.c: $(srcdir)/emulparams/cgc_i386_be.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386_be "$(tdir_cgc_i386_be)"
ecgc_i386_chaos.c: $(srcdir)/emulparams/cgc_i386_chaos.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc_chaos.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386_chaos "$(tdir_cgc_i386_chaos)"
ecgc_i386_fbsd.c: $(srcdir)/emulparams/cgc_i386_fbsd.sh \
  $(srcdir)/emulparams/cgc_i386.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386_fbsd "$(tdir_cgc_i386_fbsd)"
ecgc_i386_ldso.c: $(srcdir)/emulparams/cgc_i386_ldso.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386_ldso "$(tdir_cgc_i386_ldso)"
ecgc_i386_nacl.c: $(srcdir)/emulparams/cgc_i386_nacl.sh \
  $(srcdir)/emulparams/cgc_i386.sh \
  $(srcdir)/emulparams/cgc_nacl.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386_nacl "$(tdir_cgc_i386_nacl)"
ecgc_i386_sol2.c: $(srcdir)/emulparams/cgc_i386_sol2.sh \
  $(srcdir)/emulparams/solaris2.sh \
  $(srcdir)/emultempl/solaris2.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386_sol2 "$(tdir_cgc_i386_sol2)"
ecgc_i386_vxworks.c: $(srcdir)/emulparams/cgc_i386_vxworks.sh \
  $(srcdir)/emulparams/vxworks.sh $(srcdir)/emultempl/vxworks.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_i386_vxworks "$(tdir_cgc_i386_vxworks)"
ecgc_s390.c: $(srcdir)/emulparams/cgc_s390.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_s390 "$(tdir_cgc_s390)"
egld960.c: $(srcdir)/emulparams/gld960.sh \
  $(srcdir)/emultempl/gld960.em $(srcdir)/scripttempl/i960.sc ${GEN_DEPENDS}
	${GENSCRIPTS} gld960 "$(tdir_gld960)"
egld960coff.c: $(srcdir)/emulparams/gld960coff.sh \
  $(srcdir)/emultempl/gld960c.em $(srcdir)/scripttempl/i960.sc ${GEN_DEPENDS}
	${GENSCRIPTS} gld960coff "$(tdir_gld960coff)"
eh8300.c: $(srcdir)/emulparams/h8300.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8300.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300 "$(tdir_h8300)"
eh8300cgc.c: $(srcdir)/emulparams/h8300cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300cgc "$(tdir_h8300cgc)"
eh8300h.c: $(srcdir)/emulparams/h8300h.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8300h.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300h "$(tdir_h8300h)"
eh8300hcgc.c: $(srcdir)/emulparams/h8300hcgc.sh \
  $(srcdir)/emulparams/h8300cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300hcgc "$(tdir_h8300hcgc)"
eh8300hn.c: $(srcdir)/emulparams/h8300hn.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8300hn.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300hn "$(tdir_h8300hn)"
eh8300hncgc.c: $(srcdir)/emulparams/h8300hncgc.sh \
  $(srcdir)/emulparams/h8300cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300hncgc "$(tdir_h8300hncgc)"
eh8300s.c: $(srcdir)/emulparams/h8300s.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8300s.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300s "$(tdir_h8300s)"
eh8300self.c: $(srcdir)/emulparams/h8300self.sh \
  $(srcdir)/emulparams/h8300cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300self "$(tdir_h8300self)"
eh8300sn.c: $(srcdir)/emulparams/h8300sn.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8300sn.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300sn "$(tdir_h8300sn)"
eh8300sncgc.c: $(srcdir)/emulparams/h8300sncgc.sh \
  $(srcdir)/emulparams/h8300cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300sncgc "$(tdir_h8300sncgc)"
eh8300sx.c: $(srcdir)/emulparams/h8300sx.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8300sx.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300sx "$(tdir_h8300sx)"
eh8300sxcgc.c: $(srcdir)/emulparams/h8300sxcgc.sh \
  $(srcdir)/emulparams/h8300cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300sxcgc "$(tdir_h8300sxcgc)"
eh8300sxn.c: $(srcdir)/emulparams/h8300sxn.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8300sxn.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300sxn "$(tdir_h8300sxn)"
eh8300sxncgc.c: $(srcdir)/emulparams/h8300sxncgc.sh \
  $(srcdir)/emulparams/h8300cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8300sxncgc "$(tdir_h8300sxncgc)"
eh8500.c: $(srcdir)/emulparams/h8500.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8500.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8500 "$(tdir_h8500)"
eh8500b.c: $(srcdir)/emulparams/h8500b.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8500b.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8500b "$(tdir_h8500b)"
eh8500c.c: $(srcdir)/emulparams/h8500c.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8500c.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8500c "$(tdir_h8500c)"
eh8500m.c: $(srcdir)/emulparams/h8500m.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8500m.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8500m "$(tdir_h8500m)"
eh8500s.c: $(srcdir)/emulparams/h8500s.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/h8500s.sc ${GEN_DEPENDS}
	${GENSCRIPTS} h8500s "$(tdir_h8500s)"
ehp300bsd.c: $(srcdir)/emulparams/hp300bsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} hp300bsd "$(tdir_hp300bsd)"
ehp3hpux.c: $(srcdir)/emulparams/hp3hpux.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} hp3hpux "$(tdir_hp3hpux)"
ehppacgc.c: $(srcdir)/emulparams/hppacgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/hppacgc.em \
  $(srcdir)/scripttempl/hppacgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} hppacgc "$(tdir_hppacgc)"
ehppalinux.c: $(srcdir)/emulparams/hppalinux.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/hppacgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} hppalinux "$(tdir_hppalinux)"
ehppanbsd.c: $(srcdir)/emulparams/hppanbsd.sh \
  $(srcdir)/emulparams/hppacgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/hppacgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} hppanbsd "$(tdir_hppanbsd)"
ehppaobsd.c: $(srcdir)/emulparams/hppaobsd.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/hppacgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} hppaobsd "$(tdir_hppaobsd)"
ei386aout.c: $(srcdir)/emulparams/i386aout.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386aout "$(tdir_i386aout)"
ei386beos.c: $(srcdir)/emulparams/i386beos.sh \
  $(srcdir)/emultempl/beos.em $(srcdir)/scripttempl/i386beos.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386beos "$(tdir_i386beos)"
ei386bsd.c: $(srcdir)/emulparams/i386bsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386bsd "$(tdir_i386bsd)"
ei386coff.c: $(srcdir)/emulparams/i386coff.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/i386coff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386coff "$(tdir_i386coff)"
ei386go32.c: $(srcdir)/emulparams/i386go32.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/i386go32.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386go32 "$(tdir_i386go32)"
ei386linux.c: $(srcdir)/emulparams/i386linux.sh \
  $(srcdir)/emultempl/linux.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386linux "$(tdir_i386linux)"
ei386lynx.c: $(srcdir)/emulparams/i386lynx.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386lynx "$(tdir_i386lynx)"
ei386mach.c: $(srcdir)/emulparams/i386mach.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386mach "$(tdir_i386mach)"
ei386moss.c: $(srcdir)/emulparams/i386moss.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386moss "$(tdir_i386moss)"
ei386msdos.c: $(srcdir)/emulparams/i386msdos.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/i386msdos.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386msdos "$(tdir_i386msdos)"
ei386nbsd.c:	$(srcdir)/emulparams/i386nbsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386nbsd "$(tdir_i386nbsd)"
ei386nto.c:	$(srcdir)/emulparams/i386nto.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386nto "$(tdir_i386nto)"
ei386nw.c:	$(srcdir)/emulparams/i386nw.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/nw.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386nw "$(tdir_i386nw)"
ei386pe.c: $(srcdir)/emulparams/i386pe.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/pe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386pe "$(tdir_i386pe)"
ei386pe_posix.c: $(srcdir)/emulparams/i386pe_posix.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/pe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386pe_posix "$(tdir_i386pe_posix)"
ei386pep.c: $(srcdir)/emulparams/i386pep.sh \
  $(srcdir)/emultempl/pep.em $(srcdir)/scripttempl/pep.sc ${GEN_DEPENDS}
	${GENSCRIPTS} i386pep "$(tdir_i386pe)"
elnk960.c: $(srcdir)/emulparams/lnk960.sh \
  $(srcdir)/emultempl/lnk960.em $(srcdir)/scripttempl/i960.sc ${GEN_DEPENDS}
	${GENSCRIPTS} lnk960 "$(tdir_lnk960)"
em32rcgc.c: $(srcdir)/emulparams/m32rcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m32rcgc "$(tdir_m32r)"
em32rcgc_linux.c: $(srcdir)/emulparams/m32rcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m32rcgc_linux "$(tdir_m32rcgc_linux)"
em32rlcgc.c: $(srcdir)/emulparams/m32rlcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m32rlcgc "$(tdir_m32rlcgc)"
em32rlcgc_linux.c: $(srcdir)/emulparams/m32rlcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m32rlcgc_linux "$(tdir_m32rlcgc_linux)"
em68hc11cgc.c: $(srcdir)/emulparams/m68hc11cgc.sh \
  $(srcdir)/emultempl/m68hc1xcgc.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgcm68hc11.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68hc11cgc "$(tdir_m68hc11)"
em68hc11cgcb.c: $(srcdir)/emulparams/m68hc11cgcb.sh \
  $(srcdir)/emultempl/m68hc1xcgc.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgcm68hc11.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68hc11cgcb "$(tdir_m68hc11b)"
em68hc12cgc.c: $(srcdir)/emulparams/m68hc12cgc.sh \
  $(srcdir)/emultempl/m68hc1xcgc.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgcm68hc12.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68hc12cgc "$(tdir_m68hc12)"
em68hc12cgcb.c: $(srcdir)/emulparams/m68hc12cgcb.sh \
  $(srcdir)/emultempl/m68hc1xcgc.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgcm68hc12.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68hc12cgcb "$(tdir_m68hc12b)"
em68k4knbsd.c:	$(srcdir)/emulparams/m68k4knbsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68k4knbsd "$(tdir_m68k4knbsd)"
em68kaout.c: $(srcdir)/emulparams/m68kaout.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68kaout "$(tdir_m68kaout)"
em68kaux.c: $(srcdir)/emulparams/m68kaux.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/m68kaux.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68kaux "$(tdir_m68kaux)"
em68kcoff.c: $(srcdir)/emulparams/m68kcoff.sh \
  $(srcdir)/emultempl/m68kcoff.em $(srcdir)/scripttempl/m68kcoff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68kcoff "$(tdir_m68kcoff)"
em68kcgc.c: $(srcdir)/emulparams/m68kcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/m68kcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68kcgc "$(tdir_m68kcgc)"
em68kcgcnbsd.c: $(srcdir)/emulparams/m68kcgcnbsd.sh \
  $(srcdir)/emulparams/m68kcgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/m68kcgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68kcgcnbsd "$(tdir_m68kcgcnbsd)"
em68klinux.c: $(srcdir)/emulparams/m68klinux.sh \
  $(srcdir)/emultempl/linux.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68klinux "$(tdir_m68klinux)"
em68knbsd.c:	$(srcdir)/emulparams/m68knbsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68knbsd "$(tdir_m68knbsd)"
em68kpsos.c:	$(srcdir)/emulparams/m68kpsos.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/psos.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m68kpsos "$(tdir_m68kpsos)"
em88kbcs.c: $(srcdir)/emulparams/m88kbcs.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/m88kbcs.sc ${GEN_DEPENDS}
	${GENSCRIPTS} m88kbcs "$(tdir_m88kbcs)"
emcorepe.c: $(srcdir)/emulparams/mcorepe.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/pe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} mcorepe "$(tdir_mcorepe)"
emn10200.c: $(srcdir)/emulparams/mn10200.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} mn10200 "$(tdir_mn10200)"
emn10300.c: $(srcdir)/emulparams/mn10300.sh \
  $(srcdir)/emulparams/mn10200.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} mn10300 "$(tdir_mn10300)"
emsp430x110.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x110 "$(tdir_msp430x110)" msp430all
emsp430x1101.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1101 "$(tdir_msp430x1101)" msp430all
emsp430x1111.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1111 "$(tdir_msp430x1111)" msp430all
emsp430x112.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x112 "$(tdir_msp430x112)" msp430all
emsp430x1121.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1121 "$(tdir_msp430x1121)" msp430all
emsp430x1122.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1122 "$(tdir_msp430x1122)" msp430all
emsp430x1132.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1132 "$(tdir_msp430x1132)" msp430all
emsp430x122.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x122 "$(tdir_msp430x122)" msp430all
emsp430x1222.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1222 "$(tdir_msp430x1222)" msp430all
emsp430x123.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x123 "$(tdir_msp430x123)" msp430all
emsp430x1232.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1232 "$(tdir_msp430x1232)" msp430all
emsp430x133.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x133 "$(tdir_msp430x133)" msp430all
emsp430x1331.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1331 "$(tdir_msp430x1331)" msp430all
emsp430x135.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x135 "$(tdir_msp430x135)" msp430all
emsp430x1351.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1351 "$(tdir_msp430x1351)" msp430all
emsp430x147.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x147 "$(tdir_msp430x147)" msp430all
emsp430x148.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x148 "$(tdir_msp430x148)" msp430all
emsp430x149.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x149 "$(tdir_msp430x149)" msp430all
emsp430x155.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x155 "$(tdir_msp430x155)" msp430all
emsp430x156.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x156 "$(tdir_msp430x156)" msp430all
emsp430x157.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x157 "$(tdir_msp430x157)" msp430all
emsp430x1610.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1610 "$(tdir_msp430x1610)" msp430all
emsp430x1611.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1611 "$(tdir_msp430x1611)" msp430all
emsp430x1612.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x1612 "$(tdir_msp430x1612)" msp430all
emsp430x167.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x167 "$(tdir_msp430x167)" msp430all
emsp430x168.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x168 "$(tdir_msp430x168)" msp430all
emsp430x169.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x169 "$(tdir_msp430x169)" msp430all
emsp430x2101.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x2101 "$(tdir_msp430x2101)" msp430all
emsp430x2111.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x2111 "$(tdir_msp430x2111)" msp430all
emsp430x2121.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x2121 "$(tdir_msp430x2121)" msp430all
emsp430x2131.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x2131 "$(tdir_msp430x2131)" msp430all
emsp430x311.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x311 "$(tdir_msp430x311)" msp430all
emsp430x312.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x312 "$(tdir_msp430x312)" msp430all
emsp430x313.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x313 "$(tdir_msp430x313)" msp430all
emsp430x314.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x314 "$(tdir_msp430x314)" msp430all
emsp430x315.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x315 "$(tdir_msp430x315)" msp430all
emsp430x323.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x323 "$(tdir_msp430x323)" msp430all
emsp430x325.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x325 "$(tdir_msp430x325)" msp430all
emsp430x336.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x336 "$(tdir_msp430x336)" msp430all
emsp430x337.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430_3.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x337 "$(tdir_msp430x337)" msp430all
emsp430x412.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x412 "$(tdir_msp430x412)" msp430all
emsp430x413.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x413 "$(tdir_msp430x413)" msp430all
emsp430x415.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x415 "$(tdir_msp430x415)" msp430all
emsp430x417.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x417 "$(tdir_msp430x417)" msp430all
emsp430x435.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x435 "$(tdir_msp430x435)" msp430all
emsp430x436.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x436 "$(tdir_msp430x436)" msp430all
emsp430x437.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x437 "$(tdir_msp430x437)" msp430all
emsp430x447.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x447 "$(tdir_msp430x447)" msp430all
emsp430x448.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x448 "$(tdir_msp430x448)" msp430all
emsp430x449.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430x449 "$(tdir_msp430x449)" msp430all
emsp430xE423.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xE423 "$(tdir_msp430xE423)" msp430all
emsp430xE425.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xE425 "$(tdir_msp430xE425)" msp430all
emsp430xE427.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xE427 "$(tdir_msp430xE427)" msp430all
emsp430xG437.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xG437 "$(tdir_msp430xG437)" msp430all
emsp430xG438.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xG438 "$(tdir_msp430xG438)" msp430all
emsp430xG439.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xG439 "$(tdir_msp430xG439)" msp430all
emsp430xW423.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xW423 "$(tdir_msp430xW423)" msp430all
emsp430xW425.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xW425 "$(tdir_msp430xW425)" msp430all
emsp430xW427.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430xW427 "$(tdir_msp430xW427)" msp430all
emsp430X.c: $(srcdir)/emulparams/msp430all.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc32msp430.sc \
  ${GEN_DEPENDS}
	${GENSCRIPTS} msp430X "$(tdir_msp430X)" msp430all
enews.c: $(srcdir)/emulparams/news.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} news "$(tdir_news)"
enios2cgc.c: $(srcdir)/emulparams/nios2cgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} nios2cgc "$(tdir_nios2cgc)"
enios2linux.c: $(srcdir)/emulparams/nios2linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} nios2linux "$(tdir_nios2linux)"
ens32knbsd.c:	$(srcdir)/emulparams/ns32knbsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/emultempl/netbsd.em \
  $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} ns32knbsd "$(tdir_ns32knbsd)"
eaarch64cgc.c: $(srcdir)/emulparams/aarch64cgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64cgc "$(tdir_aarch64cgc)"
eaarch64cgc32.c: $(srcdir)/emulparams/aarch64cgc32.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64cgc32 "$(tdir_aarch64cgc32)"
eaarch64cgcb.c: $(srcdir)/emulparams/aarch64cgcb.sh $(srcdir)/emulparams/aarch64cgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64cgcb "$(tdir_aarch64cgcb)"
eaarch64cgc32b.c: $(srcdir)/emulparams/aarch64cgc32b.sh $(srcdir)/emulparams/aarch64cgc32.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64cgc32b "$(tdir_aarch64cgc32b)"
eaarch64linux.c: $(srcdir)/emulparams/aarch64linux.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64linux "$(tdir_aarch64linux)"
eaarch64linuxb.c: $(srcdir)/emulparams/aarch64linuxb.sh $(srcdir)/emulparams/aarch64linux.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64linuxb "$(tdir_aarch64linuxb)"
eaarch64linux32.c: $(srcdir)/emulparams/aarch64linux32.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64linux32 "$(tdir_aarch64linux32)"
eaarch64linux32b.c: $(srcdir)/emulparams/aarch64linux32b.sh $(srcdir)/emulparams/aarch64linux32.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/aarch64cgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} aarch64linux32b "$(tdir_aarch64linux32b)"
eor32.c: $(srcdir)/emulparams/or32.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/or32.sc ${GEN_DEPENDS}
	${GENSCRIPTS} or32 "$(tdir_or32)"
eor32cgc.c: $(srcdir)/emulparams/or32cgc.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} or32cgc "$(tdir_or32cgc)"
epc532macha.c: $(srcdir)/emulparams/pc532macha.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} pc532macha "$(tdir_pc532macha)"
epdp11.c: $(srcdir)/emulparams/pdp11.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} pdp11 "$(tdir_pdp11)"
epjcgc.c: $(srcdir)/emulparams/pjcgc.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} pjcgc "$(tdir_pjcgc)"
epjlcgc.c: $(srcdir)/emulparams/pjlcgc.sh $(srcdir)/emulparams/pjcgc.sh \
  $(CGC_GEN_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} pjlcgc "$(tdir_pjlcgc)"
eppclynx.c: $(srcdir)/emulparams/ppclynx.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} ppclynx "$(tdir_ppclynx)"
eppcmacos.c:	$(srcdir)/emulparams/ppcmacos.sh \
  $(srcdir)/emultempl/aix.em $(srcdir)/scripttempl/aix.sc ${GEN_DEPENDS}
	${GENSCRIPTS} ppcmacos "$(tdir_ppcmacos)"
eppcnw.c:	$(srcdir)/emulparams/ppcnw.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/nw.sc ${GEN_DEPENDS}
	${GENSCRIPTS} ppcnw "$(tdir_ppcnw)"
eppcpe.c: $(srcdir)/emulparams/ppcpe.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/ppcpe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} ppcpe "$(tdir_ppcpe)"
eriscix.c: $(srcdir)/emulparams/riscix.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} riscix "$(tdir_riscix)"
escore3_cgc.c: $(srcdir)/emulparams/scorecgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/scorecgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} score3_cgc "$(tdir_score3_cgc)" scorecgc
escore7_cgc.c: $(srcdir)/emulparams/scorecgc.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/scorecgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} score7_cgc "$(tdir_score7_cgc)" scorecgc
esh.c: $(srcdir)/emulparams/sh.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/sh.sc ${GEN_DEPENDS}
	${GENSCRIPTS} sh "$(tdir_sh)"
eshcgc.c: $(srcdir)/emulparams/shcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc "$(tdir_shcgc)"
eshcgc32.c: $(srcdir)/emulparams/shcgc32.sh \
  $(BFDDIR)/libbfd.h $(INCDIR)/libiberty.h \
  $(srcdir)/emultempl/sh64cgc.em $(INCDIR)/cgc/sh.h $(BFDDIR)/cgc-bfd.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc32 "$(tdir_shcgc32)"
eshcgc32_linux.c: $(srcdir)/emulparams/shcgc32_linux.sh \
  $(srcdir)/emulparams/shcgc32.sh \
  $(BFDDIR)/libbfd.h $(INCDIR)/libiberty.h \
  $(srcdir)/emultempl/sh64cgc.em $(INCDIR)/cgc/sh.h $(BFDDIR)/cgc-bfd.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc32_linux "$(tdir_shcgc32_linux)"
eshcgc32_nbsd.c: $(srcdir)/emulparams/shcgc32_nbsd.sh \
  $(srcdir)/emulparams/shcgc32.sh \
  $(BFDDIR)/libbfd.h $(INCDIR)/libiberty.h \
  $(srcdir)/emultempl/sh64cgc.em $(INCDIR)/cgc/sh.h $(BFDDIR)/cgc-bfd.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc32_nbsd "$(tdir_shcgc32_nbsd)"
eshcgc_fd.c: $(srcdir)/emulparams/shcgc_fd.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc_fd "$(tdir_shcgc_fd)"
eshcgc_linux.c: $(srcdir)/emulparams/shcgc_linux.sh \
  $(srcdir)/emulparams/shlcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc_linux "$(tdir_shcgc_linux)"
eshcgc_nbsd.c: $(srcdir)/emulparams/shcgc_nbsd.sh \
  $(srcdir)/emulparams/shcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc_nbsd "$(tdir_shcgc_nbsd)"
eshcgc_nto.c: $(srcdir)/emulparams/shcgc_nto.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc_nto "$(tdir_shcgc_nto)"
eshcgc_uclinux.c: $(srcdir)/emulparams/shcgc_uclinux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc_uclinux "$(tdir_shcgc_uclinux)"
eshcgc_vxworks.c: $(srcdir)/emulparams/shcgc_vxworks.sh \
  $(srcdir)/emulparams/vxworks.sh $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc \
  $(srcdir)/emultempl/vxworks.em ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc_vxworks "$(tdir_shcgc_vxworks)"
eshl.c: $(srcdir)/emulparams/shl.sh \
  $(srcdir)/emulparams/sh.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/sh.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shl "$(tdir_shl)"
eshlcgc.c: $(srcdir)/emulparams/shlcgc.sh \
  $(srcdir)/emulparams/shcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc "$(tdir_shlcgc)"
eshlcgc32.c: $(srcdir)/emulparams/shlcgc32.sh \
  $(BFDDIR)/libbfd.h $(INCDIR)/libiberty.h $(srcdir)/emulparams/shcgc32.sh \
  $(srcdir)/emultempl/sh64cgc.em $(INCDIR)/cgc/sh.h $(BFDDIR)/cgc-bfd.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc32 "$(tdir_shlcgc32)"
eshlcgc32_linux.c: $(srcdir)/emulparams/shlcgc32_linux.sh \
  $(srcdir)/emulparams/shcgc32_linux.sh $(srcdir)/emulparams/shcgc32.sh \
  $(BFDDIR)/libbfd.h $(INCDIR)/libiberty.h \
  $(srcdir)/emultempl/sh64cgc.em $(INCDIR)/cgc/sh.h $(BFDDIR)/cgc-bfd.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc32_linux "$(tdir_shlcgc32_linux)"
eshlcgc32_nbsd.c: $(srcdir)/emulparams/shlcgc32_nbsd.sh \
  $(srcdir)/emulparams/shcgc32_nbsd.sh $(srcdir)/emulparams/shcgc32.sh \
  $(BFDDIR)/libbfd.h $(INCDIR)/libiberty.h \
  $(srcdir)/emultempl/sh64cgc.em $(INCDIR)/cgc/sh.h $(BFDDIR)/cgc-bfd.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc32_nbsd "$(tdir_shlcgc32_nbsd)"
eshlcgc_fd.c: $(srcdir)/emulparams/shlcgc_fd.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc_fd "$(tdir_shlcgc_fd)"
eshlcgc_linux.c: $(srcdir)/emulparams/shlcgc_linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc_linux "$(tdir_shlcgc_linux)"
eshlcgc_nbsd.c: $(srcdir)/emulparams/shlcgc_nbsd.sh \
  $(srcdir)/emulparams/shcgc_nbsd.sh \
  $(srcdir)/emulparams/shcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc_nbsd "$(tdir_shlcgc_nbsd)"
eshlcgc_nto.c: $(srcdir)/emulparams/shlcgc_nto.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc_nto "$(tdir_shlcgc_nto)"
eshlcgc_vxworks.c: $(srcdir)/emulparams/shlcgc_vxworks.sh \
  $(srcdir)/emulparams/shcgc_vxworks.sh $(srcdir)/emulparams/vxworks.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc $(srcdir)/emultempl/vxworks.em \
  ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc_vxworks "$(tdir_shlcgc_vxworks)"
eshlsymbian.c: $(srcdir)/emulparams/shlsymbian.sh \
  $(srcdir)/emulparams/shcgc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc32sh-symbian.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlsymbian "$(tdir_shlcgc)"
eshpe.c: $(srcdir)/emulparams/shpe.sh \
  $(srcdir)/emultempl/pe.em $(srcdir)/scripttempl/pe.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shpe "$(tdir_shl)"
esparcaout.c: $(srcdir)/emulparams/sparcaout.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} sparcaout "$(tdir_sparcaout)"
esparclinux.c: $(srcdir)/emulparams/sparclinux.sh \
  $(srcdir)/emultempl/linux.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} sparclinux "$(tdir_sparclinux)"
esparcnbsd.c:	$(srcdir)/emulparams/sparcnbsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} sparcnbsd "$(tdir_sparcnbsd)"
est2000.c: $(srcdir)/emulparams/st2000.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/st2000.sc ${GEN_DEPENDS}
	${GENSCRIPTS} st2000 "$(tdir_st2000)"
esun3.c: $(srcdir)/emulparams/sun3.sh \
  $(srcdir)/emultempl/sunos.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} sun3 "$(tdir_sun3)"
esun4.c: $(srcdir)/emulparams/sun4.sh \
  $(srcdir)/emultempl/sunos.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} sun4 "$(tdir_sun4)"
etic30aout.c: $(srcdir)/emulparams/tic30aout.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/tic30aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} tic30aout "$(tdir_tic30aout)"
etic30coff.c: $(srcdir)/emulparams/tic30coff.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/tic30coff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} tic30coff "$(tdir_tic30coff)"
etic3xcoff.c: $(srcdir)/emulparams/tic3xcoff.sh \
  $(srcdir)/emultempl/ticoff.em $(srcdir)/scripttempl/tic4xcoff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} tic3xcoff "$(tdir_tic4xcoff)"
etic3xcoff_onchip.c: $(srcdir)/emulparams/tic3xcoff_onchip.sh \
  $(srcdir)/emultempl/ticoff.em $(srcdir)/scripttempl/tic4xcoff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} tic3xcoff_onchip "$(tdir_tic4xcoff)"
etic4xcoff.c: $(srcdir)/emulparams/tic4xcoff.sh \
  $(srcdir)/emultempl/ticoff.em $(srcdir)/scripttempl/tic4xcoff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} tic4xcoff "$(tdir_tic4xcoff)"
etic54xcoff.c: $(srcdir)/emulparams/tic54xcoff.sh \
  $(srcdir)/emultempl/ticoff.em $(srcdir)/scripttempl/tic54xcoff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} tic54xcoff "$(tdir_tic54xcoff)"
etic80coff.c: $(srcdir)/emulparams/tic80coff.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/tic80coff.sc ${GEN_DEPENDS}
	${GENSCRIPTS} tic80coff "$(tdir_tic80coff)"
ev850.c: $(srcdir)/emulparams/v850.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/v850.sc ${GEN_DEPENDS}
	${GENSCRIPTS} v850 "$(tdir_v850)"
ev850_rh850.c: $(srcdir)/emulparams/v850_rh850.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/v850_rh850.sc ${GEN_DEPENDS}
	${GENSCRIPTS} v850_rh850 "$(tdir_v850_rh850)"
evanilla.c: $(srcdir)/emulparams/vanilla.sh \
  $(srcdir)/emultempl/vanilla.em $(srcdir)/scripttempl/vanilla.sc ${GEN_DEPENDS}
	${GENSCRIPTS} vanilla "$(tdir_vanilla)"
evax.c: $(srcdir)/emulparams/vax.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} vax "$(tdir_vax)"
evaxnbsd.c: $(srcdir)/emulparams/vaxnbsd.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} vaxnbsd "$(tdir_vaxnbsd)"
evsta.c: $(srcdir)/emulparams/vsta.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/aout.sc ${GEN_DEPENDS}
	${GENSCRIPTS} vsta "$(tdir_vsta)"
ew65.c: $(srcdir)/emulparams/w65.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/w65.sc ${GEN_DEPENDS}
	${GENSCRIPTS} w65 "$(tdir_w65)"
exgatecgc.c: $(srcdir)/emulparams/xgatecgc.sh \
  $(srcdir)/emultempl/generic.em $(CGC_DEPS) \
  $(srcdir)/scripttempl/cgcxgate.sc ${GEN_DEPENDS}
	${GENSCRIPTS} xgatecgc "$(tdir_xgate)"
ez80.c: $(srcdir)/emulparams/z80.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/emultempl/z80.em \
  $(srcdir)/scripttempl/z80.sc ${GEN_DEPENDS}
	${GENSCRIPTS} z80 "$(tdir_z80)"
ez8001.c: $(srcdir)/emulparams/z8001.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/z8000.sc ${GEN_DEPENDS}
	${GENSCRIPTS} z8001 "$(tdir_z8001)"
ez8002.c: $(srcdir)/emulparams/z8002.sh \
  $(srcdir)/emultempl/generic.em $(srcdir)/scripttempl/z8000.sc ${GEN_DEPENDS}
	${GENSCRIPTS} z8002 "$(tdir_z8002)"

ecgc32_x86_64.c: $(srcdir)/emulparams/cgc32_x86_64.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_x86_64 "$(tdir_cgc32_x86_64)"
ecgc32_x86_64_nacl.c: $(srcdir)/emulparams/cgc32_x86_64_nacl.sh \
  $(srcdir)/emulparams/cgc32_x86_64.sh \
  $(srcdir)/emulparams/cgc_nacl.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc32_x86_64_nacl "$(tdir_cgc32_x86_64_nacl)"
ecgc64_aix.c: $(srcdir)/emulparams/cgc64_aix.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_aix "$(tdir_cgc64_aix)"
ecgc64_ia64.c: $(srcdir)/emulparams/cgc64_ia64.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/ia64cgc.em \
  $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_ia64 "$(tdir_cgc64_ia64)"
ecgc64_ia64_fbsd.c: $(srcdir)/emulparams/cgc64_ia64_fbsd.sh \
  $(srcdir)/emulparams/cgc64_ia64.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/ia64cgc.em \
  $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_ia64_fbsd "$(tdir_cgc64_ia64_fbsd)"
ecgc64_ia64_vms.c: $(srcdir)/emulparams/cgc64_ia64_vms.sh \
  $(srcdir)/emultempl/vms.em $(srcdir)/emultempl/cgc-generic.em \
  $(srcdir)/scripttempl/ia64vms.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_ia64_vms "$(tdir_cgc64_ia64_vms)"
ecgc64_s390.c: $(srcdir)/emulparams/cgc64_s390.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_s390 "$(tdir_cgc64_s390)"
ecgc64_sparc.c: $(srcdir)/emulparams/cgc64_sparc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_sparc "$(tdir_cgc64_sparc)"
ecgc64_sparc_fbsd.c: $(srcdir)/emulparams/cgc64_sparc_fbsd.sh \
  $(srcdir)/emulparams/cgc64_sparc.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_sparc_fbsd "$(tdir_cgc64_sparc_fbsd)"
ecgc64_sparc_sol2.c: $(srcdir)/emulparams/cgc64_sparc_sol2.sh \
  $(srcdir)/emulparams/cgc64_sparc.sh \
  $(srcdir)/emulparams/solaris2.sh \
  $(srcdir)/emultempl/solaris2.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64_sparc_sol2 "$(tdir_cgc64_sparc_sol2)"
ecgc64alpha.c: $(srcdir)/emulparams/cgc64alpha.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/alphacgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64alpha "$(tdir_cgc64alpha)"
ecgc64alpha_fbsd.c: $(srcdir)/emulparams/cgc64alpha_fbsd.sh \
  $(srcdir)/emulparams/cgc64alpha.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/alphacgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64alpha_fbsd "$(tdir_cgc64alpha_fbsd)"
ecgc64alpha_nbsd.c: $(srcdir)/emulparams/cgc64alpha_nbsd.sh \
  $(srcdir)/emulparams/cgc64alpha.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/alphacgc.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64alpha_nbsd "$(tdir_cgc64alpha_nbsd)"
ecgc64bmip.c: $(srcdir)/emulparams/cgc64bmip.sh \
  $(srcdir)/emulparams/cgc64bmip-defs.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/irix.em $(srcdir)/emultempl/mipself.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64bmip "$(tdir_cgc64bmip)"
ecgc64btsmip.c: $(srcdir)/emulparams/cgc64btsmip.sh \
  $(srcdir)/emulparams/cgc64bmip-defs.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64btsmip "$(tdir_cgc64btsmip)"
ecgc64btsmip_fbsd.c: $(srcdir)/emulparams/cgc64btsmip_fbsd.sh \
  $(srcdir)/emulparams/cgc64bmip-defs.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64btsmip_fbsd "$(tdir_cgc64btsmip_fbsd)"
ecgc64hppa.c: $(srcdir)/emulparams/cgc64hppa.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc64hppa.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64hppa "$(tdir_cgc64hppa)"
ecgc64lppc.c: $(srcdir)/emulparams/cgc64lppc.sh \
  $(srcdir)/emulparams/cgc64ppc.sh $(srcdir)/emultempl/ppc64cgc.em \
  ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64lppc "$(tdir_cgc64lppc)"
ecgc64ltsmip.c: $(srcdir)/emulparams/cgc64ltsmip.sh \
  $(srcdir)/emulparams/cgc64btsmip.sh $(srcdir)/emulparams/cgc64bmip-defs.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64ltsmip "$(tdir_cgc64ltsmip)"
ecgc64ltsmip_fbsd.c: $(srcdir)/emulparams/cgc64ltsmip_fbsd.sh \
  $(srcdir)/emulparams/cgc64btsmip_fbsd.sh $(srcdir)/emulparams/cgc64bmip-defs.sh \
  $(srcdir)/emulparams/cgc32bmipn32-defs.sh $(CGC_DEPS) \
  $(srcdir)/emultempl/mipself.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64ltsmip_fbsd "$(tdir_cgc64ltsmip_fbsd)"
ecgc64mmix.c: $(srcdir)/emulparams/cgc64mmix.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/mmix-cgcnmmo.em \
  $(srcdir)/emultempl/mmixcgc.em $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64mmix "$(tdir_cgc64mmix)"
ecgc64ppc.c: $(srcdir)/emulparams/cgc64ppc.sh $(srcdir)/emultempl/ppc64cgc.em \
  ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64ppc "$(tdir_cgc64ppc)"
ecgc64ppc_fbsd.c: $(srcdir)/emulparams/cgc64ppc_fbsd.sh \
  $(srcdir)/emultempl/ppc64cgc.em ldemul-list.h \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64ppc_fbsd "$(tdir_cgc64ppc_fbsd)"
ecgc64rdos.c: $(srcdir)/emulparams/cgc64rdos.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64rdos "$(tdir_cgc64rdos)"
ecgc64tilegx.c: $(srcdir)/emulparams/cgc64tilegx.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64tilegx "$(tdir_tilegx)"
ecgc64tilegx_be.c: $(srcdir)/emulparams/cgc64tilegx_be.sh \
  $(CGC_DEPS) $(srcdir)/emultempl/needrelax.em \
  $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc64tilegx_be "$(tdir_tilegx_be)"
ecgc_l1om.c: $(srcdir)/emulparams/cgc_l1om.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_l1om "$(tdir_cgc_l1om)"
ecgc_l1om_fbsd.c: $(srcdir)/emulparams/cgc_l1om_fbsd.sh \
  $(srcdir)/emulparams/cgc_l1om.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_l1om_fbsd "$(tdir_cgc_l1om_fbsd)"
ecgc_k1om.c: $(srcdir)/emulparams/cgc_k1om.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_k1om "$(tdir_cgc_k1om)"
ecgc_k1om_fbsd.c: $(srcdir)/emulparams/cgc_k1om_fbsd.sh \
  $(srcdir)/emulparams/cgc_k1om.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_k1om_fbsd "$(tdir_cgc_k1om_fbsd)"
ecgc_x86_64.c: $(srcdir)/emulparams/cgc_x86_64.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_x86_64 "$(tdir_cgc_x86_64)"
ecgc_x86_64_fbsd.c: $(srcdir)/emulparams/cgc_x86_64_fbsd.sh \
  $(srcdir)/emulparams/cgc_x86_64.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_x86_64_fbsd "$(tdir_cgc_x86_64_fbsd)"
ecgc_x86_64_nacl.c: $(srcdir)/emulparams/cgc_x86_64_nacl.sh \
  $(srcdir)/emulparams/cgc_x86_64.sh \
  $(srcdir)/emulparams/cgc_nacl.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_x86_64_nacl "$(tdir_cgc_x86_64_nacl)"
ecgc_x86_64_sol2.c: $(srcdir)/emulparams/cgc_x86_64_sol2.sh \
  $(srcdir)/emulparams/cgc_x86_64.sh \
  $(srcdir)/emulparams/solaris2.sh \
  $(srcdir)/emultempl/solaris2.em \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} cgc_x86_64_sol2 "$(tdir_cgc_x86_64_sol2)"
ehppa64linux.c: $(srcdir)/emulparams/hppa64linux.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} hppa64linux "$(tdir_hppa64linux)"
emmo.c: $(srcdir)/emulparams/mmo.sh $(srcdir)/emultempl/mmix-cgcnmmo.em \
  $(srcdir)/emultempl/generic.em $(srcdir)/emultempl/cgc-generic.em \
  $(srcdir)/emultempl/mmo.em $(srcdir)/scripttempl/DWARF.sc \
  $(srcdir)/scripttempl/mmo.sc ${GEN_DEPENDS}
	${GENSCRIPTS} mmo "$(tdir_mmo)"
eshcgc64.c: $(srcdir)/emulparams/shcgc64.sh $(srcdir)/emulparams/shcgc32.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc64 "$(tdir_shcgc64)"
eshcgc64_nbsd.c: $(srcdir)/emulparams/shcgc64_nbsd.sh \
  $(srcdir)/emulparams/shcgc32_nbsd.sh $(srcdir)/emulparams/shcgc32.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shcgc64_nbsd "$(tdir_shcgc64_nbsd)"
eshlcgc64.c: $(srcdir)/emulparams/shlcgc64.sh \
  $(srcdir)/emulparams/shcgc64.sh $(srcdir)/emulparams/shcgc32.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc64 "$(tdir_shlcgc64)"
eshlcgc64_nbsd.c: $(srcdir)/emulparams/shlcgc64_nbsd.sh \
  $(srcdir)/emulparams/shcgc64_nbsd.sh \
  $(srcdir)/emulparams/shcgc32_nbsd.sh $(srcdir)/emulparams/shcgc32.sh \
  $(CGC_DEPS) $(srcdir)/scripttempl/cgc.sc ${GEN_DEPENDS}
	${GENSCRIPTS} shlcgc64_nbsd "$(tdir_shlcgc64_nbsd)"

# We need this for automake to use YLWRAP.
EXTRA_ld_new_SOURCES = deffilep.y ldlex.l
# Allow dependency tracking to work for these files, too.
EXTRA_ld_new_SOURCES += pep-dll.c pe-dll.c

ld_new_SOURCES = ldgram.y ldlex-wrapper.c lexsup.c ldlang.c mri.c ldctor.c ldmain.c \
	ldwrite.c ldexp.c ldemul.c ldver.c ldmisc.c ldfile.c ldcref.c $(PLUGIN_C)
ld_new_DEPENDENCIES = $(EMULATION_OFILES) $(EMUL_EXTRA_OFILES) $(BFDLIB) $(LIBIBERTY) $(LIBINTL_DEP)
ld_new_LDADD = $(EMULATION_OFILES) $(EMUL_EXTRA_OFILES) $(BFDLIB) $(LIBIBERTY) $(LIBINTL)

# Dependency tracking for the generated emulation files.
EXTRA_ld_new_SOURCES += $(ALL_EMULATION_SOURCES) $(ALL_64_EMULATION_SOURCES)

# This is the real libbfd.a created by libtool.
TESTBFDLIB = @TESTBFDLIB@

check-DEJAGNU: site.exp
	srcroot=`cd $(srcdir) && pwd`; export srcroot; \
	r=`pwd`; export r; \
	LC_ALL=C; export LC_ALL; \
	EXPECT=$(EXPECT); export EXPECT; \
	runtest=$(RUNTEST); \
	if $(SHELL) -c "$$runtest --version" > /dev/null 2>&1; then \
	  $$runtest --tool $(DEJATOOL) --srcdir $${srcroot}/testsuite \
		CC="$(CC_FOR_TARGET)" CFLAGS="$(CFLAGS)" \
		CXX="$(CXX_FOR_TARGET)" CXXFLAGS="$(CXXFLAGS)" \
		CC_FOR_HOST="$(CC)" CFLAGS_FOR_HOST="$(CFLAGS)" \
		OFILES="$(OFILES)" BFDLIB="$(TESTBFDLIB)" \
		LIBIBERTY="$(LIBIBERTY) $(LIBINTL)" LIBS="$(LIBS)" \
		DO_COMPARE="`echo '$(do_compare)' | sed -e 's,\\$$,,g'`" \
		$(RUNTESTFLAGS); \
	else echo "WARNING: could not find \`runtest'" 1>&2; :;\
	fi

# Rules for testing by relinking ld itself.
# A similar test is in the testsuite.  This target is for ease of use
# when porting ld.

ld-partial.@OBJEXT@: ld-new$(EXEEXT)
	./ld-new$(EXEEXT) $(HOSTING_EMU) -o ld-partial.@OBJEXT@ -r $(OFILES)
ld1$(EXEEXT): ld-partial.@OBJEXT@
	./ld-new$(EXEEXT) $(HOSTING_EMU) -o ld1$(EXEEXT) $(HOSTING_CRT0) ld-partial.@OBJEXT@ $(TESTBFDLIB) $(LIBIBERTY) $(HOSTING_LIBS) $(LIBS)

ld1-full$(EXEEXT): ld-new
	./ld-new$(EXEEXT) $(HOSTING_EMU) -o ld1-full$(EXEEXT) $(HOSTING_CRT0) $(OFILES) $(TESTBFDLIB) $(LIBIBERTY) $(HOSTING_LIBS) $(LIBS)

ld2$(EXEEXT): ld1$(EXEEXT)
	./ld1$(EXEEXT) $(HOSTING_EMU) -o ld2$(EXEEXT) $(HOSTING_CRT0) $(OFILES) $(TESTBFDLIB) $(LIBIBERTY) $(HOSTING_LIBS) $(LIBS)

ld3$(EXEEXT): ld2$(EXEEXT)
	./ld2$(EXEEXT) $(HOSTING_EMU) -o ld3$(EXEEXT) $(HOSTING_CRT0) $(OFILES) $(TESTBFDLIB) $(LIBIBERTY) $(HOSTING_LIBS) $(LIBS)

bootstrap: ld3$(EXEEXT)
	cmp ld2$(EXEEXT) ld3$(EXEEXT)

.PHONY: bootstrap

# A test program for C++ constructors and destructors.
# This test is now in the testsuite.
#
#cdtest: cdtest-main.@OBJEXT@ cdtest-bar.@OBJEXT@ cdtest-foo.@OBJEXT@ ld.new
#	./ld.new $(HOSTING_EMU) -o cdtest $(HOSTING_CRT0) \
#	  cdtest-main.@OBJEXT@ cdtest-bar.@OBJEXT@ cdtest-foo.@OBJEXT@ $(HOSTING_LIBS)
#
#cdtest.out: cdtest
#	./cdtest > cdtest.tmp
#	mv cdtest.tmp cdtest.out
#
#cdtest-ur.@OBJEXT@: cdtest-main.@OBJEXT@ cdtest-bar.@OBJEXT@ cdtest-foo.@OBJEXT@ ld.new
#	./ld.new $(HOSTING_EMU) -o cdtest-ur.@OBJEXT@ -Ur cdtest-main.@OBJEXT@ \
#	  cdtest-bar.@OBJEXT@ cdtest-foo.@OBJEXT@
#
#cdtest-ur: cdtest-ur.@OBJEXT@
#	./ld.new $(HOSTING_EMU) -o cdtest-ur $(HOSTING_CRT0) cdtest-ur.@OBJEXT@ \
#	  $(HOSTING_LIBS)
#
#cdtest-ur.out: cdtest-ur
#	./cdtest-ur > cdtest-ur.tmp
#	mv cdtest-ur.tmp cdtest-ur.out
#
#check-cdtest: cdtest.out cdtest-ur.out $(srcdir)/cdtest.exp
#	diff $(srcdir)/cdtest.exp cdtest.out
#	diff $(srcdir)/cdtest.exp cdtest-ur.out
#
#.PHONY: check-cdtest

# END OF CHECK TARGETS

#
# Build a dummy plugin using libtool.
#
if ENABLE_PLUGINS
noinst_LTLIBRARIES = libldtestplug.la
libldtestplug_la_SOURCES = testplug.c
libldtestplug_la_CFLAGS= -g -O2
libldtestplug_la_LDFLAGS = -no-undefined -rpath /nowhere
endif

# DOCUMENTATION TARGETS
# Manual configuration file; not usually attached to normal configuration,
# because almost all configs use "gen" version of manual.
#  Set DOCVER above to change.
configdoc.texi:	${DOCVER}-doc.texi
	cp ${srcdir}/${DOCVER}-doc.texi ./configdoc.texi
	chmod u+w ./configdoc.texi

# Build the man page from the texinfo file
# The sed command removes the no-adjust Nroff command so that
# the man output looks standard.
ld.1: $(srcdir)/ld.texinfo configdoc.texi
	touch $@
	-$(TEXI2POD) $(MANCONF) < $(srcdir)/ld.texinfo > ld.pod
	-($(POD2MAN) ld.pod | \
		sed -e '/^.if n .na/d' > $@.T$$$$ && \
		mv -f $@.T$$$$ $@) || \
		(rm -f $@.T$$$$ && exit 1)
	rm -f ld.pod

MAINTAINERCLEANFILES = configdoc.texi ld.1

# We want to reconfigure if configure.host or configure.tgt changes.  We
# extract version from bfd/configure.in, so we must depend on that also.
CONFIG_STATUS_DEPENDENCIES = $(srcdir)/configure.host $(srcdir)/configure.tgt \
	$(srcdir)/../bfd/configure.in

MOSTLYCLEANFILES = $(STAGESTUFF) ld1$(EXEEXT) ld2$(EXEEXT) ld3$(EXEEXT) \
	ldemul-list.h crtbegin.@OBJEXT@ crtend.@OBJEXT@ ld.log ld.sum
mostlyclean-local:
	-rm -rf tmpdir
CLEANFILES = dep.sed DEP DEPA DEP1 DEP2 spu_ovl.s spu_ovl.@OBJEXT@ spu_icache.s spu_icache.@OBJEXT@

.PHONY: install-exec-local install-data-local

install-exec-local: ld-new$(EXEEXT) install-binPROGRAMS
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/bin
	n=`echo $(installed_linker) | sed '$(transform)'`; \
	if test "$(bindir)" != "$(tooldir)/bin"; then \
	  rm -f $(DESTDIR)$(tooldir)/bin/$(installed_linker)$(EXEEXT); \
	  ln $(DESTDIR)$(bindir)/$$n$(EXEEXT) $(DESTDIR)$(tooldir)/bin/$(installed_linker)$(EXEEXT) >/dev/null 2>/dev/null \
	  || $(LIBTOOL) --mode=install $(INSTALL_PROGRAM) ld-new$(EXEEXT) $(DESTDIR)$(tooldir)/bin/$(installed_linker)$(EXEEXT); \
	fi; \
	if test "x$(install_as_default)" = "xyes"; then \
	  ld=`echo ld | sed '$(transform)'`; \
	  rm -f $(DESTDIR)$(bindir)/$$ld$(EXEEXT); \
	  ln $(DESTDIR)$(bindir)/$$n$(EXEEXT) $(DESTDIR)$(bindir)/$$ld$(EXEEXT) >/dev/null 2>/dev/null \
	  || $(LIBTOOL) --mode=install $(INSTALL_PROGRAM) ld-new$(EXEEXT) $(DESTDIR)$(bindir)/$$ld$(EXEEXT); \
	  if test "$(bindir)" != "$(tooldir)/bin"; then \
	    rm -f $(DESTDIR)$(tooldir)/bin/ld$(EXEEXT); \
	    ln $(DESTDIR)$(bindir)/$$n$(EXEEXT) $(DESTDIR)$(tooldir)/bin/ld$(EXEEXT) >/dev/null 2>/dev/null \
	    || $(LIBTOOL) --mode=install $(INSTALL_PROGRAM) ld-new$(EXEEXT) $(DESTDIR)$(tooldir)/bin/ld$(EXEEXT); \
	  fi; \
	fi

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(scriptdir)/ldscripts
	for f in ldscripts/*; do \
	  $(INSTALL_DATA) $$f $(DESTDIR)$(scriptdir)/$$f ; \
	done

# Stuff that should be included in a distribution.  The diststuff
# target is run by the taz target in ../Makefile.in.
EXTRA_DIST = ldgram.c ldgram.h ldlex.c emultempl/spu_ovl.@OBJEXT@_c \
	     emultempl/spu_icache.@OBJEXT@_c deffilep.c deffilep.h $(man_MANS)
diststuff: info $(EXTRA_DIST)

# Both info (ld.info) and ld.1 depend on configdoc.texi.
# But info isn't a direct target. Make info-recursive to depend on
# ld.1 to support parallel build.
info-recursive: ld.1

DISTCLEANFILES = tdirs site.exp site.bak stringify.sed
distclean-local:
	rm -rf ldscripts

MAINTAINERCLEANFILES += ld.info

# Automake 1.9 will only build info files in the objdir if they are
# mentioned in DISTCLEANFILES.  It doesn't have to be unconditional,
# though, so we use a bogus condition.
if GENINSRC_NEVER
DISTCLEANFILES += ld.info
endif
