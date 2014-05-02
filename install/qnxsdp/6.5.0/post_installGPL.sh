#!/bin/sh

(
BASEDIR=$1
if test ! -r $BASEDIR/target/qnx6/armle-v7/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/bin || mkdir $BASEDIR/target/qnx6/armle-v7/bin
fi
if test -d $BASEDIR/target/qnx6/armle-v7/bin; then
   cd $BASEDIR/target/qnx6/armle-v7/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/bin"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/usr || mkdir $BASEDIR/target/qnx6/armle-v7/usr
    test -r $BASEDIR/target/qnx6/armle-v7/usr/bin || mkdir $BASEDIR/target/qnx6/armle-v7/usr/bin
fi
if test -d $BASEDIR/target/qnx6/armle-v7/usr/bin; then
   cd $BASEDIR/target/qnx6/armle-v7/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/armle/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/bin || mkdir $BASEDIR/target/qnx6/armle/bin
fi
if test -d $BASEDIR/target/qnx6/armle/bin; then
   cd $BASEDIR/target/qnx6/armle/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/bin"
fi

if test ! -r $BASEDIR/target/qnx6/armle/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/usr || mkdir $BASEDIR/target/qnx6/armle/usr
    test -r $BASEDIR/target/qnx6/armle/usr/bin || mkdir $BASEDIR/target/qnx6/armle/usr/bin
fi
if test -d $BASEDIR/target/qnx6/armle/usr/bin; then
   cd $BASEDIR/target/qnx6/armle/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/bin || mkdir $BASEDIR/target/qnx6/mipsbe/bin
fi
if test -d $BASEDIR/target/qnx6/mipsbe/bin; then
   cd $BASEDIR/target/qnx6/mipsbe/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/usr || mkdir $BASEDIR/target/qnx6/mipsbe/usr
    test -r $BASEDIR/target/qnx6/mipsbe/usr/bin || mkdir $BASEDIR/target/qnx6/mipsbe/usr/bin
fi
if test -d $BASEDIR/target/qnx6/mipsbe/usr/bin; then
   cd $BASEDIR/target/qnx6/mipsbe/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/bin || mkdir $BASEDIR/target/qnx6/mipsle/bin
fi
if test -d $BASEDIR/target/qnx6/mipsle/bin; then
   cd $BASEDIR/target/qnx6/mipsle/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/usr || mkdir $BASEDIR/target/qnx6/mipsle/usr
    test -r $BASEDIR/target/qnx6/mipsle/usr/bin || mkdir $BASEDIR/target/qnx6/mipsle/usr/bin
fi
if test -d $BASEDIR/target/qnx6/mipsle/usr/bin; then
   cd $BASEDIR/target/qnx6/mipsle/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/bin || mkdir $BASEDIR/target/qnx6/ppcbe-spe/bin
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/bin; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr/bin || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr/bin
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/usr/bin; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/bin || mkdir $BASEDIR/target/qnx6/ppcbe/bin
fi
if test -d $BASEDIR/target/qnx6/ppcbe/bin; then
   cd $BASEDIR/target/qnx6/ppcbe/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/usr || mkdir $BASEDIR/target/qnx6/ppcbe/usr
    test -r $BASEDIR/target/qnx6/ppcbe/usr/bin || mkdir $BASEDIR/target/qnx6/ppcbe/usr/bin
fi
if test -d $BASEDIR/target/qnx6/ppcbe/usr/bin; then
   cd $BASEDIR/target/qnx6/ppcbe/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/shle/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/bin || mkdir $BASEDIR/target/qnx6/shle/bin
fi
if test -d $BASEDIR/target/qnx6/shle/bin; then
   cd $BASEDIR/target/qnx6/shle/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/bin"
fi

if test ! -r $BASEDIR/target/qnx6/shle/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/usr || mkdir $BASEDIR/target/qnx6/shle/usr
    test -r $BASEDIR/target/qnx6/shle/usr/bin || mkdir $BASEDIR/target/qnx6/shle/usr/bin
fi
if test -d $BASEDIR/target/qnx6/shle/usr/bin; then
   cd $BASEDIR/target/qnx6/shle/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/x86/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/bin || mkdir $BASEDIR/target/qnx6/x86/bin
fi
if test -d $BASEDIR/target/qnx6/x86/bin; then
   cd $BASEDIR/target/qnx6/x86/bin
   ln -s -f gunzip uncompress
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/bin"
fi

if test ! -r $BASEDIR/target/qnx6/x86/usr/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/usr || mkdir $BASEDIR/target/qnx6/x86/usr
    test -r $BASEDIR/target/qnx6/x86/usr/bin || mkdir $BASEDIR/target/qnx6/x86/usr/bin
fi
if test -d $BASEDIR/target/qnx6/x86/usr/bin; then
   cd $BASEDIR/target/qnx6/x86/usr/bin
   ln -s -f gawk awk
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/usr/bin"
fi

) >/tmp/qnxlink.log 2>&1
