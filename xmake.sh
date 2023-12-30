#!/bin/sh
# 1. Put here the path on which the cross compiler and other tools
# for the target will be found with standard names.

# Note: these paths are Mac OS X specific.
XC_PATH=$HOME/djgpp/bin
XPREFIX=i586-pc-msdosdjgpp-

# 2. Put here the path for where things are to be installed.
# You should have created the lib, info and include directories
# in this directory.

# Note: unused. I don't recommend using install, it probably
# won't work correctly. (msikma, 2016)
INSTALL_BASE=$HOME/djgpp/

# Set up some environment variables and export them to GNU make.

CROSSCOMPILE=1
MINGDIR=$INSTALL_BASE
DJDIR=$INSTALL_BASE
NATIVEPATH=$PATH
PATH=$XC_PATH:$NATIVEPATH

export CROSSCOMPILE MINGDIR DJDIR NATIVEPATH PATH XPREFIX

make all 
