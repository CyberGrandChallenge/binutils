. ${srcdir}/emulparams/cgc32_x86_64.sh
. ${srcdir}/emulparams/cgc_nacl.sh
OUTPUT_FORMAT="cgc32-x86-64-nacl"
ARCH="i386:x64-32:nacl"	# The :nacl just means one-byte nops for code fill.
