#!/bin/bash

# you must source the file to have changes reflect
# in current env eg.
# ". ./cgc-dev-switch.sh"
# or
# "source ./cgc-dev-switch.sh"

# attempt to detect when script is run without sourcing
test x${BASH} = x/bin/bash || "$? : script should be sourced"
test x${BASH} = x/bin/bash || exit 1
test x${0} = x"-bash" || "$? : script should be sourced"
test x${0} = x"-bash" || exit 1

MYPATH=$PATH
CGCPATH=/usr/i386-linux-cgc/bin


# PATH=/usr/i386-linux-cgc/bin/:$PATH

if [ "${PATH/$CGCPATH}" = "$PATH" ] ;
then
#  echo "CGC build dir not in path ($CGCPATH)"
  PATH=$CGCPATH:$MYPATH
  export PATH
  echo "set for CGC building"
else
#  echo "CGC build dir in path ($CGCPATH)"
  PATH=`echo $MYPATH | sed "s_$CGCPATH:__g"`
  export PATH
  echo "set for non-CGC building"
fi
