. ${srcdir}/emulparams/cgc_x86_64.sh
. ${srcdir}/emulparams/cgc_nacl.sh
OUTPUT_FORMAT="cgc64-x86-64-nacl"
ARCH="i386:x86-64:nacl"	# The :nacl just means one-byte nops for code fill.
