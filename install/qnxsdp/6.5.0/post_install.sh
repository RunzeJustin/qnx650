#!/bin/sh

(
BASEDIR=$1
if test ! -r $BASEDIR/host/linux/x86/unsupported/python25/bin; then
    test -r $BASEDIR/host || mkdir $BASEDIR/host
    test -r $BASEDIR/host/linux || mkdir $BASEDIR/host/linux
    test -r $BASEDIR/host/linux/x86 || mkdir $BASEDIR/host/linux/x86
    test -r $BASEDIR/host/linux/x86/unsupported || mkdir $BASEDIR/host/linux/x86/unsupported
    test -r $BASEDIR/host/linux/x86/unsupported/python25 || mkdir $BASEDIR/host/linux/x86/unsupported/python25
    test -r $BASEDIR/host/linux/x86/unsupported/python25/bin || mkdir $BASEDIR/host/linux/x86/unsupported/python25/bin
fi
if test -d $BASEDIR/host/linux/x86/unsupported/python25/bin; then
   cd $BASEDIR/host/linux/x86/unsupported/python25/bin
   ln -s -f python2.5-config python-config
else
   echo "Could not change to $BASEDIR/host/linux/x86/unsupported/python25/bin"
fi

if test ! -r $BASEDIR/host/linux/x86/usr/bin; then
    test -r $BASEDIR/host || mkdir $BASEDIR/host
    test -r $BASEDIR/host/linux || mkdir $BASEDIR/host/linux
    test -r $BASEDIR/host/linux/x86 || mkdir $BASEDIR/host/linux/x86
    test -r $BASEDIR/host/linux/x86/usr || mkdir $BASEDIR/host/linux/x86/usr
    test -r $BASEDIR/host/linux/x86/usr/bin || mkdir $BASEDIR/host/linux/x86/usr/bin
fi
if test -d $BASEDIR/host/linux/x86/usr/bin; then
   cd $BASEDIR/host/linux/x86/usr/bin
   ln -s -f mips-unknown-nto-qnx6.5.0-gprof-2.19 mips-unknown-nto-qnx6.5.0-gprof
ln -s -f arm-unknown-nto-qnx6.5.0-c++-4.4.2 arm-unknown-nto-qnx6.5.0-c++
ln -s -f arm-unknown-nto-qnx6.5.0eabi-gprof-2.19 arm-unknown-nto-qnx6.5.0eabi-gprof
ln -s -f ntomips-ar-2.19 ntomips-ar
ln -s -f ntox86-objdump-2.19 ntox86-objdump
ln -s -f i486-pc-nto-qnx6.5.0-addr2line-2.19 i486-pc-nto-qnx6.5.0-addr2line
ln -s -f ntomips-strings-2.19 ntomips-strings
ln -s -f ntoppc-objcopy-2.19 ntoppc-objcopy
ln -s -f powerpc-unknown-nto-qnx6.5.0-cpp-4.4.2 powerpc-unknown-nto-qnx6.5.0-cpp
ln -s -f mips-unknown-nto-qnx6.5.0-nm-2.19 mips-unknown-nto-qnx6.5.0-nm
ln -s -f ntox86-strings-2.19 ntox86-strings
ln -s -f ntoppc-ar-2.19 ntoppc-ar
ln -s -f powerpc-unknown-nto-qnx6.5.0-addr2line-2.19 powerpc-unknown-nto-qnx6.5.0-addr2line
ln -s -f powerpc-unknown-nto-qnx6.5.0-gcc-4.4.2 powerpc-unknown-nto-qnx6.5.0-gcc
ln -s -f sh-unknown-nto-qnx6.5.0-g++-4.4.2 ntosh-g++
ln -s -f ntoppc-nm-2.19 ntoppc-nm
ln -s -f mips-unknown-nto-qnx6.5.0-readelf-2.19 mips-unknown-nto-qnx6.5.0-readelf
ln -s -f sh-unknown-nto-qnx6.5.0-ld-2.19 sh-unknown-nto-qnx6.5.0-ld
ln -s -f ntoppc-size-2.19 ntoppc-size
ln -s -f ntosh-strip-2.19 ntosh-strip
ln -s -f i486-pc-nto-qnx6.5.0-strings-2.19 i486-pc-nto-qnx6.5.0-strings
ln -s -f arm-unknown-nto-qnx6.5.0-gcc-4.4.2 ntoarm-gcc-4.4.2
ln -s -f ntoarm-ar-2.19 ntoarm-ar
ln -s -f sh-unknown-nto-qnx6.5.0-addr2line-2.19 sh-unknown-nto-qnx6.5.0-addr2line
ln -s -f arm-unknown-nto-qnx6.5.0eabi-c++-4.4.2 ntoarmv7-c++-4.4.2
ln -s -f i486-pc-nto-qnx6.5.0-objcopy-2.19 i486-pc-nto-qnx6.5.0-objcopy
ln -s -f arm-unknown-nto-qnx6.5.0eabi-g++-4.4.2 ntoarmv7-g++
ln -s -f ntosh-strings-2.19 ntosh-strings
ln -s -f i486-pc-nto-qnx6.5.0-ar-2.19 i486-pc-nto-qnx6.5.0-ar
ln -s -f mips-unknown-nto-qnx6.5.0-addr2line-2.19 mips-unknown-nto-qnx6.5.0-addr2line
ln -s -f i486-pc-nto-qnx6.5.0-g++-4.4.2 i486-pc-nto-qnx6.5.0-g++
ln -s -f ntoarmv7-ld-2.19 ntoarmv7-ld
ln -s -f ntoarmv7-readelf-2.19 ntoarmv7-readelf
ln -s -f arm-unknown-nto-qnx6.5.0-g++-4.4.2 ntoarm-g++
ln -s -f i486-pc-nto-qnx6.5.0-strip-2.19 i486-pc-nto-qnx6.5.0-strip
ln -s -f mips-unknown-nto-qnx6.5.0-c++-4.4.2 ntomips-c++
ln -s -f sh-unknown-nto-qnx6.5.0-cpp-4.4.2 ntosh-cpp
ln -s -f i486-pc-nto-qnx6.5.0-ranlib-2.19 i486-pc-nto-qnx6.5.0-ranlib
ln -s -f arm-unknown-nto-qnx6.5.0eabi-nm-2.19 arm-unknown-nto-qnx6.5.0eabi-nm
ln -s -f arm-unknown-nto-qnx6.5.0-gcov-4.4.2 ntoarm-gcov
ln -s -f ntosh-ranlib-2.19 ntosh-ranlib
ln -s -f sh-unknown-nto-qnx6.5.0-cpp-4.4.2 ntosh-cpp-4.4.2
ln -s -f powerpc-unknown-nto-qnx6.5.0-objcopy-2.19 powerpc-unknown-nto-qnx6.5.0-objcopy
ln -s -f sh-unknown-nto-qnx6.5.0-size-2.19 sh-unknown-nto-qnx6.5.0-size
ln -s -f mips-unknown-nto-qnx6.5.0-strings-2.19 mips-unknown-nto-qnx6.5.0-strings
ln -s -f powerpc-unknown-nto-qnx6.5.0-cpp-4.4.2 ntoppc-cpp
ln -s -f arm-unknown-nto-qnx6.5.0-g++-4.4.2 arm-unknown-nto-qnx6.5.0-g++
ln -s -f arm-unknown-nto-qnx6.5.0eabi-cpp-4.4.2 arm-unknown-nto-qnx6.5.0eabi-cpp
ln -s -f ntoppc-c++filt-2.19 ntoppc-c++filt
ln -s -f arm-unknown-nto-qnx6.5.0-size-2.19 arm-unknown-nto-qnx6.5.0-size
ln -s -f powerpc-unknown-nto-qnx6.5.0-as-2.19 powerpc-unknown-nto-qnx6.5.0-as
ln -s -f arm-unknown-nto-qnx6.5.0eabi-ar-2.19 arm-unknown-nto-qnx6.5.0eabi-ar
ln -s -f sh-unknown-nto-qnx6.5.0-c++filt-2.19 sh-unknown-nto-qnx6.5.0-c++filt
ln -s -f ntomips-strip-2.19 ntomips-strip
ln -s -f arm-unknown-nto-qnx6.5.0eabi-g++-4.4.2 ntoarmv7-g++-4.4.2
ln -s -f mips-unknown-nto-qnx6.5.0-cpp-4.4.2 ntomips-cpp-4.4.2
ln -s -f ntosh-ld-2.19 ntosh-ld
ln -s -f arm-unknown-nto-qnx6.5.0-objdump-2.19 arm-unknown-nto-qnx6.5.0-objdump
ln -s -f i486-pc-nto-qnx6.5.0-c++-4.4.2 ntox86-c++-4.4.2
ln -s -f ntosh-objcopy-2.19 ntosh-objcopy
ln -s -f powerpc-unknown-nto-qnx6.5.0-c++-4.4.2 powerpc-unknown-nto-qnx6.5.0-c++
ln -s -f sh-unknown-nto-qnx6.5.0-cpp-4.4.2 sh-unknown-nto-qnx6.5.0-cpp
ln -s -f powerpc-unknown-nto-qnx6.5.0-c++-4.4.2 ntoppc-c++
ln -s -f ntoarm-strip-2.19 ntoarm-strip
ln -s -f arm-unknown-nto-qnx6.5.0-nm-2.19 arm-unknown-nto-qnx6.5.0-nm
ln -s -f ntox86-ar-2.19 ntox86-ar
ln -s -f arm-unknown-nto-qnx6.5.0eabi-size-2.19 arm-unknown-nto-qnx6.5.0eabi-size
ln -s -f ntosh-objdump-2.19 ntosh-objdump
ln -s -f arm-unknown-nto-qnx6.5.0eabi-c++filt-2.19 arm-unknown-nto-qnx6.5.0eabi-c++filt
ln -s -f ntoarm-size-2.19 ntoarm-size
ln -s -f ntox86-nm-2.19 ntox86-nm
ln -s -f mips-unknown-nto-qnx6.5.0-objdump-2.19 mips-unknown-nto-qnx6.5.0-objdump
ln -s -f arm-unknown-nto-qnx6.5.0-c++-4.4.2 ntoarm-c++
ln -s -f sh-unknown-nto-qnx6.5.0-gcc-4.4.2 ntosh-gcc
ln -s -f arm-unknown-nto-qnx6.5.0eabi-gcc-4.4.2 ntoarmv7-gcc
ln -s -f ntox86-addr2line-2.19 ntox86-addr2line
ln -s -f ntosh-readelf-2.19 ntosh-readelf
ln -s -f ntoarmv7-size-2.19 ntoarmv7-size
ln -s -f arm-unknown-nto-qnx6.5.0eabi-c++-4.4.2 arm-unknown-nto-qnx6.5.0eabi-c++
ln -s -f i486-pc-nto-qnx6.5.0-gcc-4.4.2 i486-pc-nto-qnx6.5.0-gcc
ln -s -f arm-unknown-nto-qnx6.5.0eabi-ld-2.19 arm-unknown-nto-qnx6.5.0eabi-ld
ln -s -f ntoarm-strings-2.19 ntoarm-strings
ln -s -f i486-pc-nto-qnx6.5.0-gcov-4.4.2 ntox86-gcov-4.4.2
ln -s -f ntoarmv7-ranlib-2.19 ntoarmv7-ranlib
ln -s -f arm-unknown-nto-qnx6.5.0eabi-ranlib-2.19 arm-unknown-nto-qnx6.5.0eabi-ranlib
ln -s -f ntoarmv7-nm-2.19 ntoarmv7-nm
ln -s -f mips-unknown-nto-qnx6.5.0-cpp-4.4.2 mips-unknown-nto-qnx6.5.0-cpp
ln -s -f arm-unknown-nto-qnx6.5.0-gprof-2.19 arm-unknown-nto-qnx6.5.0-gprof
ln -s -f powerpc-unknown-nto-qnx6.5.0-g++-4.4.2 powerpc-unknown-nto-qnx6.5.0-g++
ln -s -f sh-unknown-nto-qnx6.5.0-gcov-4.4.2 ntosh-gcov-4.4.2
ln -s -f qcc CC
ln -s -f mips-unknown-nto-qnx6.5.0-strip-2.19 mips-unknown-nto-qnx6.5.0-strip
ln -s -f mips-unknown-nto-qnx6.5.0-c++-4.4.2 mips-unknown-nto-qnx6.5.0-c++
ln -s -f qcc cc
ln -s -f ntox86-as-2.19 ntox86-as
ln -s -f arm-unknown-nto-qnx6.5.0-c++filt-2.19 arm-unknown-nto-qnx6.5.0-c++filt
ln -s -f ntoarmv7-gprof-2.19 ntoarmv7-gprof
ln -s -f ntox86-ranlib-2.19 ntox86-ranlib
ln -s -f sh-unknown-nto-qnx6.5.0-ar-2.19 sh-unknown-nto-qnx6.5.0-ar
ln -s -f i486-pc-nto-qnx6.5.0-gprof-2.19 i486-pc-nto-qnx6.5.0-gprof
ln -s -f powerpc-unknown-nto-qnx6.5.0-ranlib-2.19 powerpc-unknown-nto-qnx6.5.0-ranlib
ln -s -f ntox86-c++filt-2.19 ntox86-c++filt
ln -s -f arm-unknown-nto-qnx6.5.0eabi-objcopy-2.19 arm-unknown-nto-qnx6.5.0eabi-objcopy
ln -s -f i486-pc-nto-qnx6.5.0-cpp-4.4.2 ntox86-cpp
ln -s -f ntox86-ld-2.19 ntox86-ld
ln -s -f arm-unknown-nto-qnx6.5.0eabi-gcc-4.4.2 arm-unknown-nto-qnx6.5.0eabi-gcc
ln -s -f ntoppc-addr2line-2.19 ntoppc-addr2line
ln -s -f arm-unknown-nto-qnx6.5.0-c++-4.4.2 ntoarm-c++-4.4.2
ln -s -f ntoarm-ld-2.19 ntoarm-ld
ln -s -f arm-unknown-nto-qnx6.5.0eabi-g++-4.4.2 arm-unknown-nto-qnx6.5.0eabi-g++
ln -s -f sh-unknown-nto-qnx6.5.0-c++-4.4.2 sh-unknown-nto-qnx6.5.0-c++
ln -s -f powerpc-unknown-nto-qnx6.5.0-strip-2.19 powerpc-unknown-nto-qnx6.5.0-strip
ln -s -f i486-pc-nto-qnx6.5.0-gcov-4.4.2 ntox86-gcov
ln -s -f arm-unknown-nto-qnx6.5.0-gcc-4.4.2 arm-unknown-nto-qnx6.5.0-gcc
ln -s -f sh-unknown-nto-qnx6.5.0-gcov-4.4.2 ntosh-gcov
ln -s -f ntoarmv7-strip-2.19 ntoarmv7-strip
ln -s -f arm-unknown-nto-qnx6.5.0eabi-gcov-4.4.2 ntoarmv7-gcov-4.4.2
ln -s -f arm-unknown-nto-qnx6.5.0eabi-strip-2.19 arm-unknown-nto-qnx6.5.0eabi-strip
ln -s -f i486-pc-nto-qnx6.5.0-cpp-4.4.2 i486-pc-nto-qnx6.5.0-cpp
ln -s -f arm-unknown-nto-qnx6.5.0-gcov-4.4.2 arm-unknown-nto-qnx6.5.0-gcov
ln -s -f mips-unknown-nto-qnx6.5.0-gcc-4.4.2 mips-unknown-nto-qnx6.5.0-gcc
ln -s -f powerpc-unknown-nto-qnx6.5.0-nm-2.19 powerpc-unknown-nto-qnx6.5.0-nm
ln -s -f flex flex++
ln -s -f ntoarm-objcopy-2.19 ntoarm-objcopy
ln -s -f powerpc-unknown-nto-qnx6.5.0-gcov-4.4.2 powerpc-unknown-nto-qnx6.5.0-gcov
ln -s -f i486-pc-nto-qnx6.5.0-as-2.19 i486-pc-nto-qnx6.5.0-as
ln -s -f i486-pc-nto-qnx6.5.0-cpp-4.4.2 ntox86-cpp-4.4.2
ln -s -f ntoarm-objdump-2.19 ntoarm-objdump
ln -s -f ntox86-size-2.19 ntox86-size
ln -s -f ntosh-gprof-2.19 ntosh-gprof
ln -s -f ntoarmv7-as-2.19 ntoarmv7-as
ln -s -f arm-unknown-nto-qnx6.5.0-ar-2.19 arm-unknown-nto-qnx6.5.0-ar
ln -s -f i486-pc-nto-qnx6.5.0-gcov-4.4.2 i486-pc-nto-qnx6.5.0-gcov
ln -s -f ntoarmv7-ar-2.19 ntoarmv7-ar
ln -s -f ntox86-objcopy-2.19 ntox86-objcopy
ln -s -f arm-unknown-nto-qnx6.5.0eabi-gcc-4.4.2 ntoarmv7-gcc-4.4.2
ln -s -f mips-unknown-nto-qnx6.5.0-ld-2.19 mips-unknown-nto-qnx6.5.0-ld
ln -s -f mips-unknown-nto-qnx6.5.0-as-2.19 mips-unknown-nto-qnx6.5.0-as
ln -s -f ntosh-ar-2.19 ntosh-ar
ln -s -f i486-pc-nto-qnx6.5.0-ld-2.19 i486-pc-nto-qnx6.5.0-ld
ln -s -f i486-pc-nto-qnx6.5.0-readelf-2.19 i486-pc-nto-qnx6.5.0-readelf
ln -s -f sh-unknown-nto-qnx6.5.0-c++-4.4.2 ntosh-c++
ln -s -f arm-unknown-nto-qnx6.5.0eabi-cpp-4.4.2 ntoarmv7-cpp
ln -s -f arm-unknown-nto-qnx6.5.0eabi-cpp-4.4.2 ntoarmv7-cpp-4.4.2
ln -s -f arm-unknown-nto-qnx6.5.0eabi-addr2line-2.19 arm-unknown-nto-qnx6.5.0eabi-addr2line
ln -s -f qcc QCC
ln -s -f arm-unknown-nto-qnx6.5.0-gcc-4.4.2 ntoarm-gcc
ln -s -f arm-unknown-nto-qnx6.5.0-cpp-4.4.2 arm-unknown-nto-qnx6.5.0-cpp
ln -s -f ntoppc-strip-2.19 ntoppc-strip
ln -s -f mips-unknown-nto-qnx6.5.0-gcov-4.4.2 ntomips-gcov
ln -s -f ntoarmv7-objcopy-2.19 ntoarmv7-objcopy
ln -s -f ntosh-size-2.19 ntosh-size
ln -s -f powerpc-unknown-nto-qnx6.5.0-g++-4.4.2 ntoppc-g++
ln -s -f powerpc-unknown-nto-qnx6.5.0-size-2.19 powerpc-unknown-nto-qnx6.5.0-size
ln -s -f ntoppc-gprof-2.19 ntoppc-gprof
ln -s -f powerpc-unknown-nto-qnx6.5.0-gcc-4.4.2 ntoppc-gcc
ln -s -f ntoarm-gprof-2.19 ntoarm-gprof
ln -s -f powerpc-unknown-nto-qnx6.5.0-c++-4.4.2 ntoppc-c++-4.4.2
ln -s -f ntox86-readelf-2.19 ntox86-readelf
ln -s -f powerpc-unknown-nto-qnx6.5.0-gcc-4.4.2 ntoppc-gcc-4.4.2
ln -s -f ntoarm-as-2.19 ntoarm-as
ln -s -f ntoarmv7-c++filt-2.19 ntoarmv7-c++filt
ln -s -f mips-unknown-nto-qnx6.5.0-objcopy-2.19 mips-unknown-nto-qnx6.5.0-objcopy
ln -s -f i486-pc-nto-qnx6.5.0-nm-2.19 i486-pc-nto-qnx6.5.0-nm
ln -s -f sh-unknown-nto-qnx6.5.0-objdump-2.19 sh-unknown-nto-qnx6.5.0-objdump
ln -s -f i486-pc-nto-qnx6.5.0-gcc-4.4.2 ntox86-gcc-4.4.2
ln -s -f arm-unknown-nto-qnx6.5.0eabi-gcov-4.4.2 arm-unknown-nto-qnx6.5.0eabi-gcov
ln -s -f ntomips-size-2.19 ntomips-size
ln -s -f ntoppc-strings-2.19 ntoppc-strings
ln -s -f arm-unknown-nto-qnx6.5.0-objcopy-2.19 arm-unknown-nto-qnx6.5.0-objcopy
ln -s -f arm-unknown-nto-qnx6.5.0eabi-strings-2.19 arm-unknown-nto-qnx6.5.0eabi-strings
ln -s -f ntox86-gprof-2.19 ntox86-gprof
ln -s -f powerpc-unknown-nto-qnx6.5.0-strings-2.19 powerpc-unknown-nto-qnx6.5.0-strings
ln -s -f ntosh-nm-2.19 ntosh-nm
ln -s -f sh-unknown-nto-qnx6.5.0-gcc-4.4.2 ntosh-gcc-4.4.2
ln -s -f ntomips-readelf-2.19 ntomips-readelf
ln -s -f mips-unknown-nto-qnx6.5.0-g++-4.4.2 ntomips-g++
ln -s -f ntoppc-as-2.19 ntoppc-as
ln -s -f sh-unknown-nto-qnx6.5.0-strings-2.19 sh-unknown-nto-qnx6.5.0-strings
ln -s -f ntoarm-readelf-2.19 ntoarm-readelf
ln -s -f ntomips-objcopy-2.19 ntomips-objcopy
ln -s -f ntomips-as-2.19 ntomips-as
ln -s -f i486-pc-nto-qnx6.5.0-gcc-4.4.2 ntox86-gcc
ln -s -f sh-unknown-nto-qnx6.5.0-ranlib-2.19 sh-unknown-nto-qnx6.5.0-ranlib
ln -s -f i486-pc-nto-qnx6.5.0-size-2.19 i486-pc-nto-qnx6.5.0-size
ln -s -f arm-unknown-nto-qnx6.5.0eabi-readelf-2.19 arm-unknown-nto-qnx6.5.0eabi-readelf
ln -s -f ntomips-c++filt-2.19 ntomips-c++filt
ln -s -f ntoarm-nm-2.19 ntoarm-nm
ln -s -f i486-pc-nto-qnx6.5.0-c++-4.4.2 ntox86-c++
ln -s -f ntoarmv7-strings-2.19 ntoarmv7-strings
ln -s -f mkxfs mkefs
ln -s -f ntomips-objdump-2.19 ntomips-objdump
ln -s -f arm-unknown-nto-qnx6.5.0-ld-2.19 arm-unknown-nto-qnx6.5.0-ld
ln -s -f sh-unknown-nto-qnx6.5.0-c++-4.4.2 ntosh-c++-4.4.2
ln -s -f sh-unknown-nto-qnx6.5.0-g++-4.4.2 ntosh-g++-4.4.2
ln -s -f ntomips-ranlib-2.19 ntomips-ranlib
ln -s -f ntosh-as-2.19 ntosh-as
ln -s -f i486-pc-nto-qnx6.5.0-g++-4.4.2 ntox86-g++
ln -s -f sh-unknown-nto-qnx6.5.0-g++-4.4.2 sh-unknown-nto-qnx6.5.0-g++
ln -s -f ntoppc-readelf-2.19 ntoppc-readelf
ln -s -f mips-unknown-nto-qnx6.5.0-g++-4.4.2 mips-unknown-nto-qnx6.5.0-g++
ln -s -f sh-unknown-nto-qnx6.5.0-gcov-4.4.2 sh-unknown-nto-qnx6.5.0-gcov
ln -s -f mips-unknown-nto-qnx6.5.0-gcc-4.4.2 ntomips-gcc
ln -s -f ntosh-c++filt-2.19 ntosh-c++filt
ln -s -f arm-unknown-nto-qnx6.5.0-cpp-4.4.2 ntoarm-cpp
ln -s -f powerpc-unknown-nto-qnx6.5.0-ar-2.19 powerpc-unknown-nto-qnx6.5.0-ar
ln -s -f ntoarm-c++filt-2.19 ntoarm-c++filt
ln -s -f mips-unknown-nto-qnx6.5.0-gcc-4.4.2 ntomips-gcc-4.4.2
ln -s -f ntox86-strip-2.19 ntox86-strip
ln -s -f arm-unknown-nto-qnx6.5.0eabi-objdump-2.19 arm-unknown-nto-qnx6.5.0eabi-objdump
ln -s -f ntoarmv7-objdump-2.19 ntoarmv7-objdump
ln -s -f ntomips-ld-2.19 ntomips-ld
ln -s -f ntoarm-ranlib-2.19 ntoarm-ranlib
ln -s -f arm-unknown-nto-qnx6.5.0-addr2line-2.19 arm-unknown-nto-qnx6.5.0-addr2line
ln -s -f ntoppc-objdump-2.19 ntoppc-objdump
ln -s -f i486-pc-nto-qnx6.5.0-objdump-2.19 i486-pc-nto-qnx6.5.0-objdump
ln -s -f mips-unknown-nto-qnx6.5.0-gcov-4.4.2 ntomips-gcov-4.4.2
ln -s -f powerpc-unknown-nto-qnx6.5.0-gcov-4.4.2 ntoppc-gcov
ln -s -f i486-pc-nto-qnx6.5.0-c++-4.4.2 i486-pc-nto-qnx6.5.0-c++
ln -s -f mips-unknown-nto-qnx6.5.0-c++-4.4.2 ntomips-c++-4.4.2
ln -s -f arm-unknown-nto-qnx6.5.0-g++-4.4.2 ntoarm-g++-4.4.2
ln -s -f ntoarm-addr2line-2.19 ntoarm-addr2line
ln -s -f arm-unknown-nto-qnx6.5.0-ranlib-2.19 arm-unknown-nto-qnx6.5.0-ranlib
ln -s -f mkxfs mkifs
ln -s -f arm-unknown-nto-qnx6.5.0-strings-2.19 arm-unknown-nto-qnx6.5.0-strings
ln -s -f powerpc-unknown-nto-qnx6.5.0-readelf-2.19 powerpc-unknown-nto-qnx6.5.0-readelf
ln -s -f arm-unknown-nto-qnx6.5.0-strip-2.19 arm-unknown-nto-qnx6.5.0-strip
ln -s -f i486-pc-nto-qnx6.5.0-c++filt-2.19 i486-pc-nto-qnx6.5.0-c++filt
ln -s -f flex lex
ln -s -f arm-unknown-nto-qnx6.5.0-cpp-4.4.2 ntoarm-cpp-4.4.2
ln -s -f ntomips-nm-2.19 ntomips-nm
ln -s -f powerpc-unknown-nto-qnx6.5.0-cpp-4.4.2 ntoppc-cpp-4.4.2
ln -s -f sh-unknown-nto-qnx6.5.0-nm-2.19 sh-unknown-nto-qnx6.5.0-nm
ln -s -f powerpc-unknown-nto-qnx6.5.0-gprof-2.19 powerpc-unknown-nto-qnx6.5.0-gprof
ln -s -f mips-unknown-nto-qnx6.5.0-ranlib-2.19 mips-unknown-nto-qnx6.5.0-ranlib
ln -s -f mips-unknown-nto-qnx6.5.0-ar-2.19 mips-unknown-nto-qnx6.5.0-ar
ln -s -f mkxfs mketfs
ln -s -f sh-unknown-nto-qnx6.5.0-strip-2.19 sh-unknown-nto-qnx6.5.0-strip
ln -s -f powerpc-unknown-nto-qnx6.5.0-g++-4.4.2 ntoppc-g++-4.4.2
ln -s -f powerpc-unknown-nto-qnx6.5.0-ld-2.19 powerpc-unknown-nto-qnx6.5.0-ld
ln -s -f arm-unknown-nto-qnx6.5.0eabi-as-2.19 arm-unknown-nto-qnx6.5.0eabi-as
ln -s -f ../photon/appbuilder/phabbind phabbind
ln -s -f sh-unknown-nto-qnx6.5.0-gcc-4.4.2 sh-unknown-nto-qnx6.5.0-gcc
ln -s -f powerpc-unknown-nto-qnx6.5.0-gcov-4.4.2 ntoppc-gcov-4.4.2
ln -s -f arm-unknown-nto-qnx6.5.0-readelf-2.19 arm-unknown-nto-qnx6.5.0-readelf
ln -s -f mips-unknown-nto-qnx6.5.0-gcov-4.4.2 mips-unknown-nto-qnx6.5.0-gcov
ln -s -f mips-unknown-nto-qnx6.5.0-g++-4.4.2 ntomips-g++-4.4.2
ln -s -f arm-unknown-nto-qnx6.5.0-as-2.19 arm-unknown-nto-qnx6.5.0-as
ln -s -f mips-unknown-nto-qnx6.5.0-size-2.19 mips-unknown-nto-qnx6.5.0-size
ln -s -f arm-unknown-nto-qnx6.5.0eabi-c++-4.4.2 ntoarmv7-c++
ln -s -f sh-unknown-nto-qnx6.5.0-objcopy-2.19 sh-unknown-nto-qnx6.5.0-objcopy
ln -s -f mips-unknown-nto-qnx6.5.0-c++filt-2.19 mips-unknown-nto-qnx6.5.0-c++filt
ln -s -f mips-unknown-nto-qnx6.5.0-cpp-4.4.2 ntomips-cpp
ln -s -f arm-unknown-nto-qnx6.5.0-gcov-4.4.2 ntoarm-gcov-4.4.2
ln -s -f sh-unknown-nto-qnx6.5.0-as-2.19 sh-unknown-nto-qnx6.5.0-as
ln -s -f i486-pc-nto-qnx6.5.0-g++-4.4.2 ntox86-g++-4.4.2
ln -s -f ntoppc-ld-2.19 ntoppc-ld
ln -s -f ntoppc-ranlib-2.19 ntoppc-ranlib
ln -s -f powerpc-unknown-nto-qnx6.5.0-c++filt-2.19 powerpc-unknown-nto-qnx6.5.0-c++filt
ln -s -f sh-unknown-nto-qnx6.5.0-gprof-2.19 sh-unknown-nto-qnx6.5.0-gprof
ln -s -f ntomips-gprof-2.19 ntomips-gprof
ln -s -f ntosh-addr2line-2.19 ntosh-addr2line
ln -s -f arm-unknown-nto-qnx6.5.0eabi-gcov-4.4.2 ntoarmv7-gcov
ln -s -f sh-unknown-nto-qnx6.5.0-readelf-2.19 sh-unknown-nto-qnx6.5.0-readelf
ln -s -f powerpc-unknown-nto-qnx6.5.0-objdump-2.19 powerpc-unknown-nto-qnx6.5.0-objdump
ln -s -f ntoarmv7-addr2line-2.19 ntoarmv7-addr2line
ln -s -f ntomips-addr2line-2.19 ntomips-addr2line
else
   echo "Could not change to $BASEDIR/host/linux/x86/usr/bin"
fi

if test ! -r $BASEDIR/host/linux/x86/usr/lib; then
    test -r $BASEDIR/host || mkdir $BASEDIR/host
    test -r $BASEDIR/host/linux || mkdir $BASEDIR/host/linux
    test -r $BASEDIR/host/linux/x86 || mkdir $BASEDIR/host/linux/x86
    test -r $BASEDIR/host/linux/x86/usr || mkdir $BASEDIR/host/linux/x86/usr
    test -r $BASEDIR/host/linux/x86/usr/lib || mkdir $BASEDIR/host/linux/x86/usr/lib
fi
if test -d $BASEDIR/host/linux/x86/usr/lib; then
   cd $BASEDIR/host/linux/x86/usr/lib
   ln -s -f libFF-T2K.so.3 libFF-T2K.so
ln -s -f libblkcache.so.2 libblkcache.so
else
   echo "Could not change to $BASEDIR/host/linux/x86/usr/lib"
fi

if test ! -r $BASEDIR/host/linux/x86/usr/lib/font; then
    test -r $BASEDIR/host || mkdir $BASEDIR/host
    test -r $BASEDIR/host/linux || mkdir $BASEDIR/host/linux
    test -r $BASEDIR/host/linux/x86 || mkdir $BASEDIR/host/linux/x86
    test -r $BASEDIR/host/linux/x86/usr || mkdir $BASEDIR/host/linux/x86/usr
    test -r $BASEDIR/host/linux/x86/usr/lib || mkdir $BASEDIR/host/linux/x86/usr/lib
    test -r $BASEDIR/host/linux/x86/usr/lib/font || mkdir $BASEDIR/host/linux/x86/usr/lib/font
fi
if test -d $BASEDIR/host/linux/x86/usr/lib/font; then
   cd $BASEDIR/host/linux/x86/usr/lib/font
   ln -s -f libFCcore.so.1 libFCcore.so
ln -s -f libPHFcore.so.1 libPHFcore.so
ln -s -f libttfFFcore.so.1 libttfFFcore.so
else
   echo "Could not change to $BASEDIR/host/linux/x86/usr/lib/font"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/bin || mkdir $BASEDIR/target/qnx6/armle-v7/bin
fi
if test -d $BASEDIR/target/qnx6/armle-v7/bin; then
   cd $BASEDIR/target/qnx6/armle-v7/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/bin"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/lib || mkdir $BASEDIR/target/qnx6/armle-v7/lib
fi
if test -d $BASEDIR/target/qnx6/armle-v7/lib; then
   cd $BASEDIR/target/qnx6/armle-v7/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libfont.so.1 libfont.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/lib"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/lib || mkdir $BASEDIR/target/qnx6/armle-v7/lib
    test -r $BASEDIR/target/qnx6/armle-v7/lib/gcc || mkdir $BASEDIR/target/qnx6/armle-v7/lib/gcc
    test -r $BASEDIR/target/qnx6/armle-v7/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/armle-v7/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/armle-v7/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/armle-v7/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/usr || mkdir $BASEDIR/target/qnx6/armle-v7/usr
    test -r $BASEDIR/target/qnx6/armle-v7/usr/lib || mkdir $BASEDIR/target/qnx6/armle-v7/usr/lib
fi
if test -d $BASEDIR/target/qnx6/armle-v7/usr/lib; then
   cd $BASEDIR/target/qnx6/armle-v7/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libGLES_CL.so.1 libGLES_CL.so
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libiow.so.1 libiow.so
ln -s -f libaoi.so.1 libaoi.so
ln -s -f libphauxrender.so.1 libphauxrender.so
ln -s -f libdisputil.so.2 libdisputil.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libPtWeb.so.3 libPtWeb.so
ln -s -f libOpenVG.so.1 libOpenVG.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libGLESv2.so.1 libGLESv2.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f libKD.so.1 libKD.so
ln -s -f libphrender.so.2 libphrender.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f libgf.so.1 libgf.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libxml2.so.1 libxml2.so
ln -s -f libFF-T2K.so.3 libFF-T2K.so
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libEGL.so.1 libEGL.so
ln -s -f libffb.so.2 libffb.so
ln -s -f libphexlib.so.3 libphexlib.so
ln -s -f libOpenVGU.so.1 libOpenVGU.so
ln -s -f libz.so.2 libz.so
ln -s -f libWFD.so.1 libWFD.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libGLES_CM.so.1 libGLES_CM.so
ln -s -f libblkcache.so.2 libblkcache.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libGLESv1_CM.so.1 libGLESv1_CM.so
ln -s -f libham.so.2 libham.so
ln -s -f libGLESv1_CL.so.1 libGLESv1_CL.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libph.so.3 libph.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/usr || mkdir $BASEDIR/target/qnx6/armle-v7/usr
    test -r $BASEDIR/target/qnx6/armle-v7/usr/lib || mkdir $BASEDIR/target/qnx6/armle-v7/usr/lib
    test -r $BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/usr/photon/savers; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/usr || mkdir $BASEDIR/target/qnx6/armle-v7/usr
    test -r $BASEDIR/target/qnx6/armle-v7/usr/photon || mkdir $BASEDIR/target/qnx6/armle-v7/usr/photon
    test -r $BASEDIR/target/qnx6/armle-v7/usr/photon/savers || mkdir $BASEDIR/target/qnx6/armle-v7/usr/photon/savers
fi
if test -d $BASEDIR/target/qnx6/armle-v7/usr/photon/savers; then
   cd $BASEDIR/target/qnx6/armle-v7/usr/photon/savers
   ln -s -f phattract phsplines
ln -s -f phattract phtails
ln -s -f phattract phpoly
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/usr/photon/savers"
fi

if test ! -r $BASEDIR/target/qnx6/armle-v7/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/usr || mkdir $BASEDIR/target/qnx6/armle-v7/usr
    test -r $BASEDIR/target/qnx6/armle-v7/usr/sbin || mkdir $BASEDIR/target/qnx6/armle-v7/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/armle-v7/usr/sbin; then
   cd $BASEDIR/target/qnx6/armle-v7/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/armle/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/bin || mkdir $BASEDIR/target/qnx6/armle/bin
fi
if test -d $BASEDIR/target/qnx6/armle/bin; then
   cd $BASEDIR/target/qnx6/armle/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/bin"
fi

if test ! -r $BASEDIR/target/qnx6/armle/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/lib || mkdir $BASEDIR/target/qnx6/armle/lib
fi
if test -d $BASEDIR/target/qnx6/armle/lib; then
   cd $BASEDIR/target/qnx6/armle/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libm-vfp.so.2 libm-vfp.so
ln -s -f libstdc++.so.5.0.7 libstdc++.so.5
ln -s -f libfont.so.1 libfont.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/lib"
fi

if test ! -r $BASEDIR/target/qnx6/armle/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/lib || mkdir $BASEDIR/target/qnx6/armle/lib
    test -r $BASEDIR/target/qnx6/armle/lib/gcc || mkdir $BASEDIR/target/qnx6/armle/lib/gcc
    test -r $BASEDIR/target/qnx6/armle/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/armle/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/armle/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/armle/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/armle/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/usr || mkdir $BASEDIR/target/qnx6/armle/usr
    test -r $BASEDIR/target/qnx6/armle/usr/lib || mkdir $BASEDIR/target/qnx6/armle/usr/lib
fi
if test -d $BASEDIR/target/qnx6/armle/usr/lib; then
   cd $BASEDIR/target/qnx6/armle/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libGLES_CL.so.1 libGLES_CL.so
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libiow.so.1 libiow.so
ln -s -f libaoi.so.1 libaoi.so
ln -s -f libphauxrender.so.1 libphauxrender.so
ln -s -f libdisputil.so.2 libdisputil.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libPtWeb.so.3 libPtWeb.so
ln -s -f libphimg.so.2 libphimg.so
ln -s -f libOpenVG.so.1 libOpenVG.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libGLESv2.so.1 libGLESv2.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f libKD.so.1 libKD.so
ln -s -f libphrender.so.2 libphrender.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f libgf.so.1 libgf.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libxml2.so.1 libxml2.so
ln -s -f libFF-T2K.so.3 libFF-T2K.so
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libEGL.so.1 libEGL.so
ln -s -f libffb.so.2 libffb.so
ln -s -f libphexlib.so.3 libphexlib.so
ln -s -f libOpenVGU.so.1 libOpenVGU.so
ln -s -f libz.so.2 libz.so
ln -s -f libWFD.so.1 libWFD.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libGLES_CM.so.1 libGLES_CM.so
ln -s -f libblkcache.so.2 libblkcache.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libGLESv1_CM.so.1 libGLESv1_CM.so
ln -s -f libham.so.2 libham.so
ln -s -f libGLESv1_CL.so.1 libGLESv1_CL.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libph.so.3 libph.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/armle/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/usr || mkdir $BASEDIR/target/qnx6/armle/usr
    test -r $BASEDIR/target/qnx6/armle/usr/lib || mkdir $BASEDIR/target/qnx6/armle/usr/lib
    test -r $BASEDIR/target/qnx6/armle/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/armle/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/armle/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/armle/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/armle/usr/photon/savers; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/usr || mkdir $BASEDIR/target/qnx6/armle/usr
    test -r $BASEDIR/target/qnx6/armle/usr/photon || mkdir $BASEDIR/target/qnx6/armle/usr/photon
    test -r $BASEDIR/target/qnx6/armle/usr/photon/savers || mkdir $BASEDIR/target/qnx6/armle/usr/photon/savers
fi
if test -d $BASEDIR/target/qnx6/armle/usr/photon/savers; then
   cd $BASEDIR/target/qnx6/armle/usr/photon/savers
   ln -s -f phattract phsplines
ln -s -f phattract phtails
ln -s -f phattract phpoly
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/usr/photon/savers"
fi

if test ! -r $BASEDIR/target/qnx6/armle/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/usr || mkdir $BASEDIR/target/qnx6/armle/usr
    test -r $BASEDIR/target/qnx6/armle/usr/sbin || mkdir $BASEDIR/target/qnx6/armle/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/armle/usr/sbin; then
   cd $BASEDIR/target/qnx6/armle/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/etc/photon; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/etc || mkdir $BASEDIR/target/qnx6/etc
    test -r $BASEDIR/target/qnx6/etc/photon || mkdir $BASEDIR/target/qnx6/etc/photon
fi
if test -d $BASEDIR/target/qnx6/etc/photon; then
   cd $BASEDIR/target/qnx6/etc/photon
   ln -s -f ../../usr/photon/config/shelf shelf
ln -s -f ../../usr/photon/config/pterm pterm
ln -s -f ../../usr/photon/config/wm wm
else
   echo "Could not change to $BASEDIR/target/qnx6/etc/photon"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/bin || mkdir $BASEDIR/target/qnx6/mipsbe/bin
fi
if test -d $BASEDIR/target/qnx6/mipsbe/bin; then
   cd $BASEDIR/target/qnx6/mipsbe/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/lib || mkdir $BASEDIR/target/qnx6/mipsbe/lib
fi
if test -d $BASEDIR/target/qnx6/mipsbe/lib; then
   cd $BASEDIR/target/qnx6/mipsbe/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libstdc++.so.5.0.7 libstdc++.so.5
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/lib"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/lib || mkdir $BASEDIR/target/qnx6/mipsbe/lib
    test -r $BASEDIR/target/qnx6/mipsbe/lib/gcc || mkdir $BASEDIR/target/qnx6/mipsbe/lib/gcc
    test -r $BASEDIR/target/qnx6/mipsbe/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/mipsbe/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/mipsbe/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/mipsbe/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/usr || mkdir $BASEDIR/target/qnx6/mipsbe/usr
    test -r $BASEDIR/target/qnx6/mipsbe/usr/lib || mkdir $BASEDIR/target/qnx6/mipsbe/usr/lib
fi
if test -d $BASEDIR/target/qnx6/mipsbe/usr/lib; then
   cd $BASEDIR/target/qnx6/mipsbe/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f libxml2.so.1 libxml2.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.3
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libz.so.2 libz.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libham.so.2 libham.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/usr || mkdir $BASEDIR/target/qnx6/mipsbe/usr
    test -r $BASEDIR/target/qnx6/mipsbe/usr/lib || mkdir $BASEDIR/target/qnx6/mipsbe/usr/lib
    test -r $BASEDIR/target/qnx6/mipsbe/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/mipsbe/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/mipsbe/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/mipsbe/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/mipsbe/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsbe || mkdir $BASEDIR/target/qnx6/mipsbe
    test -r $BASEDIR/target/qnx6/mipsbe/usr || mkdir $BASEDIR/target/qnx6/mipsbe/usr
    test -r $BASEDIR/target/qnx6/mipsbe/usr/sbin || mkdir $BASEDIR/target/qnx6/mipsbe/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/mipsbe/usr/sbin; then
   cd $BASEDIR/target/qnx6/mipsbe/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsbe/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/bin || mkdir $BASEDIR/target/qnx6/mipsle/bin
fi
if test -d $BASEDIR/target/qnx6/mipsle/bin; then
   cd $BASEDIR/target/qnx6/mipsle/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/lib || mkdir $BASEDIR/target/qnx6/mipsle/lib
fi
if test -d $BASEDIR/target/qnx6/mipsle/lib; then
   cd $BASEDIR/target/qnx6/mipsle/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libstdc++.so.5.0.7 libstdc++.so.5
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/lib"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/lib || mkdir $BASEDIR/target/qnx6/mipsle/lib
    test -r $BASEDIR/target/qnx6/mipsle/lib/gcc || mkdir $BASEDIR/target/qnx6/mipsle/lib/gcc
    test -r $BASEDIR/target/qnx6/mipsle/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/mipsle/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/mipsle/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/mipsle/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/usr || mkdir $BASEDIR/target/qnx6/mipsle/usr
    test -r $BASEDIR/target/qnx6/mipsle/usr/lib || mkdir $BASEDIR/target/qnx6/mipsle/usr/lib
fi
if test -d $BASEDIR/target/qnx6/mipsle/usr/lib; then
   cd $BASEDIR/target/qnx6/mipsle/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libphimg.so.2 libphimg.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f libxml2.so.1 libxml2.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.3
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libz.so.2 libz.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libham.so.2 libham.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/usr || mkdir $BASEDIR/target/qnx6/mipsle/usr
    test -r $BASEDIR/target/qnx6/mipsle/usr/lib || mkdir $BASEDIR/target/qnx6/mipsle/usr/lib
    test -r $BASEDIR/target/qnx6/mipsle/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/mipsle/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/mipsle/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/mipsle/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/mipsle/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/mipsle || mkdir $BASEDIR/target/qnx6/mipsle
    test -r $BASEDIR/target/qnx6/mipsle/usr || mkdir $BASEDIR/target/qnx6/mipsle/usr
    test -r $BASEDIR/target/qnx6/mipsle/usr/sbin || mkdir $BASEDIR/target/qnx6/mipsle/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/mipsle/usr/sbin; then
   cd $BASEDIR/target/qnx6/mipsle/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/mipsle/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/opt/webkit/armle/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/opt || mkdir $BASEDIR/target/qnx6/opt
    test -r $BASEDIR/target/qnx6/opt/webkit || mkdir $BASEDIR/target/qnx6/opt/webkit
    test -r $BASEDIR/target/qnx6/opt/webkit/armle || mkdir $BASEDIR/target/qnx6/opt/webkit/armle
    test -r $BASEDIR/target/qnx6/opt/webkit/armle/lib || mkdir $BASEDIR/target/qnx6/opt/webkit/armle/lib
fi
if test -d $BASEDIR/target/qnx6/opt/webkit/armle/lib; then
   cd $BASEDIR/target/qnx6/opt/webkit/armle/lib
   ln -s -f libwebkit-owb.so.1.0 libwebkit-owb.so
else
   echo "Could not change to $BASEDIR/target/qnx6/opt/webkit/armle/lib"
fi

if test ! -r $BASEDIR/target/qnx6/opt/webkit/ppcbe/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/opt || mkdir $BASEDIR/target/qnx6/opt
    test -r $BASEDIR/target/qnx6/opt/webkit || mkdir $BASEDIR/target/qnx6/opt/webkit
    test -r $BASEDIR/target/qnx6/opt/webkit/ppcbe || mkdir $BASEDIR/target/qnx6/opt/webkit/ppcbe
    test -r $BASEDIR/target/qnx6/opt/webkit/ppcbe/lib || mkdir $BASEDIR/target/qnx6/opt/webkit/ppcbe/lib
fi
if test -d $BASEDIR/target/qnx6/opt/webkit/ppcbe/lib; then
   cd $BASEDIR/target/qnx6/opt/webkit/ppcbe/lib
   ln -s -f libwebkit-owb.so.1.0 libwebkit-owb.so
else
   echo "Could not change to $BASEDIR/target/qnx6/opt/webkit/ppcbe/lib"
fi

if test ! -r $BASEDIR/target/qnx6/opt/webkit/shle/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/opt || mkdir $BASEDIR/target/qnx6/opt
    test -r $BASEDIR/target/qnx6/opt/webkit || mkdir $BASEDIR/target/qnx6/opt/webkit
    test -r $BASEDIR/target/qnx6/opt/webkit/shle || mkdir $BASEDIR/target/qnx6/opt/webkit/shle
    test -r $BASEDIR/target/qnx6/opt/webkit/shle/lib || mkdir $BASEDIR/target/qnx6/opt/webkit/shle/lib
fi
if test -d $BASEDIR/target/qnx6/opt/webkit/shle/lib; then
   cd $BASEDIR/target/qnx6/opt/webkit/shle/lib
   ln -s -f libwebkit-owb.so.1.0 libwebkit-owb.so
else
   echo "Could not change to $BASEDIR/target/qnx6/opt/webkit/shle/lib"
fi

if test ! -r $BASEDIR/target/qnx6/opt/webkit/x86/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/opt || mkdir $BASEDIR/target/qnx6/opt
    test -r $BASEDIR/target/qnx6/opt/webkit || mkdir $BASEDIR/target/qnx6/opt/webkit
    test -r $BASEDIR/target/qnx6/opt/webkit/x86 || mkdir $BASEDIR/target/qnx6/opt/webkit/x86
    test -r $BASEDIR/target/qnx6/opt/webkit/x86/lib || mkdir $BASEDIR/target/qnx6/opt/webkit/x86/lib
fi
if test -d $BASEDIR/target/qnx6/opt/webkit/x86/lib; then
   cd $BASEDIR/target/qnx6/opt/webkit/x86/lib
   ln -s -f libwebkit-owb.so.1.0 libwebkit-owb.so
else
   echo "Could not change to $BASEDIR/target/qnx6/opt/webkit/x86/lib"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/bin || mkdir $BASEDIR/target/qnx6/ppcbe-spe/bin
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/bin; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/lib || mkdir $BASEDIR/target/qnx6/ppcbe-spe/lib
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/lib; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/lib"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/lib || mkdir $BASEDIR/target/qnx6/ppcbe-spe/lib
    test -r $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc || mkdir $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc
    test -r $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr/lib || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr/lib
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/usr/lib; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libxml2.so.1 libxml2.so
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libz.so.2 libz.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libham.so.2 libham.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr/lib || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr/lib
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr
    test -r $BASEDIR/target/qnx6/ppcbe-spe/usr/sbin || mkdir $BASEDIR/target/qnx6/ppcbe-spe/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/usr/sbin; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/bin || mkdir $BASEDIR/target/qnx6/ppcbe/bin
fi
if test -d $BASEDIR/target/qnx6/ppcbe/bin; then
   cd $BASEDIR/target/qnx6/ppcbe/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/lib || mkdir $BASEDIR/target/qnx6/ppcbe/lib
fi
if test -d $BASEDIR/target/qnx6/ppcbe/lib; then
   cd $BASEDIR/target/qnx6/ppcbe/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libstdc++.so.5.0.7 libstdc++.so.5
ln -s -f libfont.so.1 libfont.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/lib"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/lib || mkdir $BASEDIR/target/qnx6/ppcbe/lib
    test -r $BASEDIR/target/qnx6/ppcbe/lib/gcc || mkdir $BASEDIR/target/qnx6/ppcbe/lib/gcc
    test -r $BASEDIR/target/qnx6/ppcbe/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/ppcbe/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/ppcbe/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/ppcbe/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/usr || mkdir $BASEDIR/target/qnx6/ppcbe/usr
    test -r $BASEDIR/target/qnx6/ppcbe/usr/lib || mkdir $BASEDIR/target/qnx6/ppcbe/usr/lib
fi
if test -d $BASEDIR/target/qnx6/ppcbe/usr/lib; then
   cd $BASEDIR/target/qnx6/ppcbe/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libGLES_CM.so libGLES_CL.so
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libGLES_CM.a libGLES_CL.a
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libiow.so.1 libiow.so
ln -s -f libaoi.so.1 libaoi.so
ln -s -f libphauxrender.so.1 libphauxrender.so
ln -s -f libdisputil.so.2 libdisputil.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libPtWeb.so.3 libPtWeb.so
ln -s -f libphimg.so.2 libphimg.so
ln -s -f libOpenVG.so.1 libOpenVG.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libGLESv2.so.1 libGLESv2.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f libKD.so.1 libKD.so
ln -s -f libphrender.so.2 libphrender.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f libgf.so.1 libgf.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libxml2.so.1 libxml2.so
ln -s -f libGLES_CMS.a libGLES_CLS.a
ln -s -f libFF-T2K.so.3 libFF-T2K.so
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libEGL.so.1 libEGL.so
ln -s -f libffb.so.2 libffb.so
ln -s -f libphexlib.so.3 libphexlib.so
ln -s -f libOpenVGU.so.1 libOpenVGU.so
ln -s -f libz.so.2 libz.so
ln -s -f libWFD.so.1 libWFD.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libGLES_CM.so.1 libGLES_CM.so
ln -s -f libblkcache.so.2 libblkcache.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libGLESv1_CM.so.1 libGLESv1_CM.so
ln -s -f libham.so.2 libham.so
ln -s -f libGLESv1_CL.so.1 libGLESv1_CL.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libph.so.3 libph.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/usr || mkdir $BASEDIR/target/qnx6/ppcbe/usr
    test -r $BASEDIR/target/qnx6/ppcbe/usr/lib || mkdir $BASEDIR/target/qnx6/ppcbe/usr/lib
    test -r $BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/usr/photon/savers; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/usr || mkdir $BASEDIR/target/qnx6/ppcbe/usr
    test -r $BASEDIR/target/qnx6/ppcbe/usr/photon || mkdir $BASEDIR/target/qnx6/ppcbe/usr/photon
    test -r $BASEDIR/target/qnx6/ppcbe/usr/photon/savers || mkdir $BASEDIR/target/qnx6/ppcbe/usr/photon/savers
fi
if test -d $BASEDIR/target/qnx6/ppcbe/usr/photon/savers; then
   cd $BASEDIR/target/qnx6/ppcbe/usr/photon/savers
   ln -s -f phattract phsplines
ln -s -f phattract phtails
ln -s -f phattract phpoly
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/usr/photon/savers"
fi

if test ! -r $BASEDIR/target/qnx6/ppcbe/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/usr || mkdir $BASEDIR/target/qnx6/ppcbe/usr
    test -r $BASEDIR/target/qnx6/ppcbe/usr/sbin || mkdir $BASEDIR/target/qnx6/ppcbe/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/ppcbe/usr/sbin; then
   cd $BASEDIR/target/qnx6/ppcbe/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/shle/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/bin || mkdir $BASEDIR/target/qnx6/shle/bin
fi
if test -d $BASEDIR/target/qnx6/shle/bin; then
   cd $BASEDIR/target/qnx6/shle/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/bin"
fi

if test ! -r $BASEDIR/target/qnx6/shle/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/lib || mkdir $BASEDIR/target/qnx6/shle/lib
fi
if test -d $BASEDIR/target/qnx6/shle/lib; then
   cd $BASEDIR/target/qnx6/shle/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libstdc++.so.5.0.7 libstdc++.so.5
ln -s -f libfont.so.1 libfont.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/lib"
fi

if test ! -r $BASEDIR/target/qnx6/shle/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/lib || mkdir $BASEDIR/target/qnx6/shle/lib
    test -r $BASEDIR/target/qnx6/shle/lib/gcc || mkdir $BASEDIR/target/qnx6/shle/lib/gcc
    test -r $BASEDIR/target/qnx6/shle/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/shle/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/shle/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/shle/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/shle/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/usr || mkdir $BASEDIR/target/qnx6/shle/usr
    test -r $BASEDIR/target/qnx6/shle/usr/lib || mkdir $BASEDIR/target/qnx6/shle/usr/lib
fi
if test -d $BASEDIR/target/qnx6/shle/usr/lib; then
   cd $BASEDIR/target/qnx6/shle/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libGLES_CM.so libGLES_CL.so
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libGLES_CM.a libGLES_CL.a
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libiow.so.1 libiow.so
ln -s -f libaoi.so.1 libaoi.so
ln -s -f libphauxrender.so.1 libphauxrender.so
ln -s -f libdisputil.so.2 libdisputil.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libPtWeb.so.3 libPtWeb.so
ln -s -f libphimg.so.2 libphimg.so
ln -s -f libOpenVG.so.1 libOpenVG.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libGLESv2.so.1 libGLESv2.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f libKD.so.1 libKD.so
ln -s -f libphrender.so.2 libphrender.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f libgf.so.1 libgf.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libxml2.so.1 libxml2.so
ln -s -f libGLES_CMS.a libGLES_CLS.a
ln -s -f libFF-T2K.so.3 libFF-T2K.so
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libEGL.so.1 libEGL.so
ln -s -f libffb.so.2 libffb.so
ln -s -f libphexlib.so.3 libphexlib.so
ln -s -f libOpenVGU.so.1 libOpenVGU.so
ln -s -f libz.so.2 libz.so
ln -s -f libWFD.so.1 libWFD.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libGLES_CM.so.1 libGLES_CM.so
ln -s -f libblkcache.so.2 libblkcache.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libGLESv1_CM.so.1 libGLESv1_CM.so
ln -s -f libham.so.2 libham.so
ln -s -f libGLESv1_CL.so.1 libGLESv1_CL.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libph.so.3 libph.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/shle/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/usr || mkdir $BASEDIR/target/qnx6/shle/usr
    test -r $BASEDIR/target/qnx6/shle/usr/lib || mkdir $BASEDIR/target/qnx6/shle/usr/lib
    test -r $BASEDIR/target/qnx6/shle/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/shle/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/shle/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/shle/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/shle/usr/photon/savers; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/usr || mkdir $BASEDIR/target/qnx6/shle/usr
    test -r $BASEDIR/target/qnx6/shle/usr/photon || mkdir $BASEDIR/target/qnx6/shle/usr/photon
    test -r $BASEDIR/target/qnx6/shle/usr/photon/savers || mkdir $BASEDIR/target/qnx6/shle/usr/photon/savers
fi
if test -d $BASEDIR/target/qnx6/shle/usr/photon/savers; then
   cd $BASEDIR/target/qnx6/shle/usr/photon/savers
   ln -s -f phattract phsplines
ln -s -f phattract phtails
ln -s -f phattract phpoly
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/usr/photon/savers"
fi

if test ! -r $BASEDIR/target/qnx6/shle/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/shle || mkdir $BASEDIR/target/qnx6/shle
    test -r $BASEDIR/target/qnx6/shle/usr || mkdir $BASEDIR/target/qnx6/shle/usr
    test -r $BASEDIR/target/qnx6/shle/usr/sbin || mkdir $BASEDIR/target/qnx6/shle/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/shle/usr/sbin; then
   cd $BASEDIR/target/qnx6/shle/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/shle/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/usr/include; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/usr || mkdir $BASEDIR/target/qnx6/usr
    test -r $BASEDIR/target/qnx6/usr/include || mkdir $BASEDIR/target/qnx6/usr/include
fi
if test -d $BASEDIR/target/qnx6/usr/include; then
   cd $BASEDIR/target/qnx6/usr/include
   ln -s -f mk/recurse.mk recurse.mk
ln -s -f mk/ab.mk ab.mk
ln -s -f sys/md5.h md5.h
ln -s -f mk/buildlist.mk buildlist.mk
ln -s -f mk/phapps.mk phapps.mk
ln -s -f sys/queue.h queue.h
ln -s -f sys/poll.h poll.h
ln -s -f curses.h ncurses.h
else
   echo "Could not change to $BASEDIR/target/qnx6/usr/include"
fi

if test ! -r $BASEDIR/target/qnx6/x86/bin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/bin || mkdir $BASEDIR/target/qnx6/x86/bin
fi
if test -d $BASEDIR/target/qnx6/x86/bin; then
   cd $BASEDIR/target/qnx6/x86/bin
   ln -s -f on waitfor
ln -s -f ../usr/bin/less more
ln -s -f elvis view
ln -s -f chown chgrp
ln -s -f elvis ex
ln -s -f pax cpio
ln -s -f ksh sh
ln -s -f elvis vi
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/bin"
fi

if test ! -r $BASEDIR/target/qnx6/x86/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/lib || mkdir $BASEDIR/target/qnx6/x86/lib
fi
if test -d $BASEDIR/target/qnx6/x86/lib; then
   cd $BASEDIR/target/qnx6/x86/lib
   ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libbessel.so.1 libbessel.so
ln -s -f libmudflap.so.0.0.0 libmudflap.so.0
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libmudflapth.so.0.0.0 libmudflapth.so.0
ln -s -f libcam.so.2 libcam.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libc.so.3 libc.so
ln -s -f libstdc++.so.5.0.7 libstdc++.so.5
ln -s -f libfont.so.1 libfont.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libstdc++.so.6.0.13 libstdc++.so.6
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libpps.so.1 libpps.so
ln -s -f libsnmp.so.1 libsnmp.so
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/lib"
fi

if test ! -r $BASEDIR/target/qnx6/x86/lib/gcc/4.4.2; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/lib || mkdir $BASEDIR/target/qnx6/x86/lib
    test -r $BASEDIR/target/qnx6/x86/lib/gcc || mkdir $BASEDIR/target/qnx6/x86/lib/gcc
    test -r $BASEDIR/target/qnx6/x86/lib/gcc/4.4.2 || mkdir $BASEDIR/target/qnx6/x86/lib/gcc/4.4.2
fi
if test -d $BASEDIR/target/qnx6/x86/lib/gcc/4.4.2; then
   cd $BASEDIR/target/qnx6/x86/lib/gcc/4.4.2
   ln -s -f ../../libcpp-ne.so.4 libcpp-ne.so
ln -s -f ../../libcpp.so.4 libcpp.so
ln -s -f ../../libstdc++.so.6 libstdc++.so
ln -s -f ../../libmudflapth.so.0 libmudflapth.so
ln -s -f ../../libmudflap.so.0 libmudflap.so
ln -s -f ../../libecpp.so.4 libecpp.so
ln -s -f ../../libecpp-ne.so.4 libecpp-ne.so
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/lib/gcc/4.4.2"
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
   ln -s -f bzdiff bzcmp
ln -s -f ../sbin/rpcbind portmap
ln -s -f freeze melt
ln -s -f hd od
ln -s -f grep egrep
ln -s -f freeze fcat
ln -s -f less more
ln -s -f bzip2 bzcat
ln -s -f grep fgrep
ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f ../../bin/ln link
ln -s -f bzgrep bzegrep
ln -s -f bzmore bzless
ln -s -f uue uuencode
ln -s -f uud uudecode
ln -s -f getconf setconf
ln -s -f ../../usr/photon/bin/inputtrap inputtrap
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/usr/bin"
fi

if test ! -r $BASEDIR/target/qnx6/x86/usr/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/usr || mkdir $BASEDIR/target/qnx6/x86/usr
    test -r $BASEDIR/target/qnx6/x86/usr/lib || mkdir $BASEDIR/target/qnx6/x86/usr/lib
fi
if test -d $BASEDIR/target/qnx6/x86/usr/lib; then
   cd $BASEDIR/target/qnx6/x86/usr/lib
   ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libGLES_CM.so libGLES_CL.so
ln -s -f libbz2.so.1.0.4 libbz2.so
ln -s -f libGLES_CM.a libGLES_CL.a
ln -s -f libfl_pic.a libflS.a
ln -s -f libcurl.so.2 libcurl.so
ln -s -f libiow.so.1 libiow.so
ln -s -f libaoi.so.1 libaoi.so
ln -s -f libphauxrender.so.1 libphauxrender.so
ln -s -f libdisputil.so.2 libdisputil.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libPtWeb.so.3 libPtWeb.so
ln -s -f libphimg.so.2 libphimg.so
ln -s -f libOpenVG.so.1 libOpenVG.so
ln -s -f libcrypto.so.1 libcrypto.so
ln -s -f libGLESv2.so.1 libGLESv2.so
ln -s -f libexpat.so.2 libexpat.so
ln -s -f libssl.so.1 libssl.so
ln -s -f libKD.so.1 libKD.so
ln -s -f libphrender.so.2 libphrender.so
ln -s -f librcheck.so.1 librcheck.so
ln -s -f libgf.so.1 libgf.so
ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libxml2.so.1 libxml2.so
ln -s -f libGLES_CMS.a libGLES_CLS.a
ln -s -f libFF-T2K.so.3 libFF-T2K.so
ln -s -f libasyncmsg.so.1 libasyncmsg.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libEGL.so.1 libEGL.so
ln -s -f libffb.so.2 libffb.so
ln -s -f libphexlib.so.3 libphexlib.so
ln -s -f libOpenVGU.so.1 libOpenVGU.so
ln -s -f ../../lib/libc.so.1 ldqnx.so.1
ln -s -f libz.so.2 libz.so
ln -s -f libWFD.so.1 libWFD.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f libGLES_CM.so.1 libGLES_CM.so
ln -s -f libblkcache.so.2 libblkcache.so
ln -s -f libmq.so.1 libmq.so
ln -s -f librpc.so.2 librpc.so
ln -s -f libGLESv1_CM.so.1 libGLESv1_CM.so
ln -s -f libham.so.2 libham.so
ln -s -f libGLESv1_CL.so.1 libGLESv1_CL.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libph.so.3 libph.so
ln -s -f libsocks.so.1 libsocks.so
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/usr/lib"
fi

if test ! -r $BASEDIR/target/qnx6/x86/usr/lib/malloc_g; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/usr || mkdir $BASEDIR/target/qnx6/x86/usr
    test -r $BASEDIR/target/qnx6/x86/usr/lib || mkdir $BASEDIR/target/qnx6/x86/usr/lib
    test -r $BASEDIR/target/qnx6/x86/usr/lib/malloc_g || mkdir $BASEDIR/target/qnx6/x86/usr/lib/malloc_g
fi
if test -d $BASEDIR/target/qnx6/x86/usr/lib/malloc_g; then
   cd $BASEDIR/target/qnx6/x86/usr/lib/malloc_g
   ln -s -f libmalloc.so.2 libmalloc.so
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/usr/lib/malloc_g"
fi

if test ! -r $BASEDIR/target/qnx6/x86/usr/photon/savers; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/usr || mkdir $BASEDIR/target/qnx6/x86/usr
    test -r $BASEDIR/target/qnx6/x86/usr/photon || mkdir $BASEDIR/target/qnx6/x86/usr/photon
    test -r $BASEDIR/target/qnx6/x86/usr/photon/savers || mkdir $BASEDIR/target/qnx6/x86/usr/photon/savers
fi
if test -d $BASEDIR/target/qnx6/x86/usr/photon/savers; then
   cd $BASEDIR/target/qnx6/x86/usr/photon/savers
   ln -s -f phattract phsplines
ln -s -f phattract phtails
ln -s -f phattract phpoly
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/usr/photon/savers"
fi

if test ! -r $BASEDIR/target/qnx6/x86/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/usr || mkdir $BASEDIR/target/qnx6/x86/usr
    test -r $BASEDIR/target/qnx6/x86/usr/sbin || mkdir $BASEDIR/target/qnx6/x86/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/x86/usr/sbin; then
   cd $BASEDIR/target/qnx6/x86/usr/sbin
   ln -s -f named-checkzone named-compilezone
ln -s -f named lwresd
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/usr/sbin"
fi

cd $BASEDIR
chmod 4775 target/qnx6/ppcbe-spe/bin/login
chmod 4775 target/qnx6/ppcbe-spe/bin/su
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/ping6
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/lprq
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/traceroute
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/lpr
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/rsh
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/rcp
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/crontab
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/traceroute6
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/rlogin
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/ping
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/newgrp
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/netstat
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/lprrm
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/passwd
chmod 4755 target/qnx6/ppcbe-spe/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/ppcbe-spe/usr/sbin/pppoed
chmod 4775 target/qnx6/ppcbe-spe/usr/sbin/dhcp.client
chmod 4775 target/qnx6/ppcbe-spe/usr/sbin/pppd
chmod 4775 target/qnx6/ppcbe-spe/sbin/pppoectl
chmod 4775 target/qnx6/ppcbe-spe/sbin/ifwatchd
chmod 4775 target/qnx6/ppcbe/bin/login
chmod 4775 target/qnx6/ppcbe/bin/su
chmod 4775 target/qnx6/ppcbe/usr/bin/ping6
chmod 4775 target/qnx6/ppcbe/usr/bin/lprq
chmod 4775 target/qnx6/ppcbe/usr/bin/traceroute
chmod 4775 target/qnx6/ppcbe/usr/bin/lpr
chmod 4775 target/qnx6/ppcbe/usr/bin/rsh
chmod 4775 target/qnx6/ppcbe/usr/bin/rcp
chmod 4775 target/qnx6/ppcbe/usr/bin/crontab
chmod 4775 target/qnx6/ppcbe/usr/bin/traceroute6
chmod 4775 target/qnx6/ppcbe/usr/bin/rlogin
chmod 4775 target/qnx6/ppcbe/usr/bin/ping
chmod 4775 target/qnx6/ppcbe/usr/bin/newgrp
chmod 4775 target/qnx6/ppcbe/usr/bin/netstat
chmod 4775 target/qnx6/ppcbe/usr/bin/lprrm
chmod 4775 target/qnx6/ppcbe/usr/bin/passwd
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/Photon
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/phshutdown
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/phrelaycfg
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/phuser
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/input-cfg
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/phlocale
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/launchmenu_notify
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/saver
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/phfont
chmod 4755 target/qnx6/ppcbe/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/ppcbe/usr/sbin/pppoed
chmod 4775 target/qnx6/ppcbe/usr/sbin/dhcp.client
chmod 4775 target/qnx6/ppcbe/usr/sbin/pppd
chmod 4775 target/qnx6/ppcbe/sbin/pppoectl
chmod 4775 target/qnx6/ppcbe/sbin/ifwatchd
chmod 4775 target/qnx6/x86/bin/login
chmod 4775 target/qnx6/x86/bin/su
chmod 4775 target/qnx6/x86/usr/bin/ping6
chmod 4775 target/qnx6/x86/usr/bin/lprq
chmod 4775 target/qnx6/x86/usr/bin/traceroute
chmod 4775 target/qnx6/x86/usr/bin/lpr
chmod 4775 target/qnx6/x86/usr/bin/rsh
chmod 4775 target/qnx6/x86/usr/bin/rcp
chmod 4775 target/qnx6/x86/usr/bin/crontab
chmod 4775 target/qnx6/x86/usr/bin/traceroute6
chmod 4775 target/qnx6/x86/usr/bin/rlogin
chmod 4775 target/qnx6/x86/usr/bin/ping
chmod 4775 target/qnx6/x86/usr/bin/newgrp
chmod 4775 target/qnx6/x86/usr/bin/netstat
chmod 4775 target/qnx6/x86/usr/bin/lprrm
chmod 4775 target/qnx6/x86/usr/bin/passwd
chmod 4775 target/qnx6/x86/usr/photon/bin/Photon
chmod 4775 target/qnx6/x86/usr/photon/bin/phshutdown
chmod 4775 target/qnx6/x86/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/x86/usr/photon/bin/phrelaycfg
chmod 4775 target/qnx6/x86/usr/photon/bin/phuser
chmod 4775 target/qnx6/x86/usr/photon/bin/input-cfg
chmod 4775 target/qnx6/x86/usr/photon/bin/phlocale
chmod 4775 target/qnx6/x86/usr/photon/bin/launchmenu_notify
chmod 4775 target/qnx6/x86/usr/photon/bin/phgrafx
chmod 4775 target/qnx6/x86/usr/photon/bin/saver
chmod 4775 target/qnx6/x86/usr/photon/bin/inputtrap
chmod 4775 target/qnx6/x86/usr/photon/bin/phfont
chmod 4755 target/qnx6/x86/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/x86/usr/sbin/pppoed
chmod 4775 target/qnx6/x86/usr/sbin/dhcp.client
chmod 4775 target/qnx6/x86/usr/sbin/pppd
chmod 4775 target/qnx6/x86/sbin/pppoectl
chmod 4775 target/qnx6/x86/sbin/ifwatchd
chmod 4775 target/qnx6/armle-v7/bin/login
chmod 4775 target/qnx6/armle-v7/bin/su
chmod 4775 target/qnx6/armle-v7/usr/bin/ping6
chmod 4775 target/qnx6/armle-v7/usr/bin/lprq
chmod 4775 target/qnx6/armle-v7/usr/bin/traceroute
chmod 4775 target/qnx6/armle-v7/usr/bin/lpr
chmod 4775 target/qnx6/armle-v7/usr/bin/rsh
chmod 4775 target/qnx6/armle-v7/usr/bin/rcp
chmod 4775 target/qnx6/armle-v7/usr/bin/crontab
chmod 4775 target/qnx6/armle-v7/usr/bin/traceroute6
chmod 4775 target/qnx6/armle-v7/usr/bin/rlogin
chmod 4775 target/qnx6/armle-v7/usr/bin/ping
chmod 4775 target/qnx6/armle-v7/usr/bin/newgrp
chmod 4775 target/qnx6/armle-v7/usr/bin/netstat
chmod 4775 target/qnx6/armle-v7/usr/bin/lprrm
chmod 4775 target/qnx6/armle-v7/usr/bin/passwd
chmod 4775 target/qnx6/armle-v7/usr/photon/bin/Photon
chmod 4775 target/qnx6/armle-v7/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/armle-v7/usr/photon/bin/phuser
chmod 4775 target/qnx6/armle-v7/usr/photon/bin/launchmenu_notify
chmod 4775 target/qnx6/armle-v7/usr/photon/bin/phfont
chmod 4755 target/qnx6/armle-v7/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/armle-v7/usr/sbin/pppoed
chmod 4775 target/qnx6/armle-v7/usr/sbin/dhcp.client
chmod 4775 target/qnx6/armle-v7/usr/sbin/pppd
chmod 4775 target/qnx6/armle-v7/sbin/pppoectl
chmod 4775 target/qnx6/armle-v7/sbin/ifwatchd
chmod 4775 target/qnx6/armle/bin/login
chmod 4775 target/qnx6/armle/bin/su
chmod 4775 target/qnx6/armle/usr/bin/ping6
chmod 4775 target/qnx6/armle/usr/bin/lprq
chmod 4775 target/qnx6/armle/usr/bin/traceroute
chmod 4775 target/qnx6/armle/usr/bin/lpr
chmod 4775 target/qnx6/armle/usr/bin/rsh
chmod 4775 target/qnx6/armle/usr/bin/rcp
chmod 4775 target/qnx6/armle/usr/bin/crontab
chmod 4775 target/qnx6/armle/usr/bin/traceroute6
chmod 4775 target/qnx6/armle/usr/bin/rlogin
chmod 4775 target/qnx6/armle/usr/bin/ping
chmod 4775 target/qnx6/armle/usr/bin/newgrp
chmod 4775 target/qnx6/armle/usr/bin/netstat
chmod 4775 target/qnx6/armle/usr/bin/lprrm
chmod 4775 target/qnx6/armle/usr/bin/passwd
chmod 4775 target/qnx6/armle/usr/photon/bin/Photon
chmod 4775 target/qnx6/armle/usr/photon/bin/phshutdown
chmod 4775 target/qnx6/armle/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/armle/usr/photon/bin/phrelaycfg
chmod 4775 target/qnx6/armle/usr/photon/bin/phuser
chmod 4775 target/qnx6/armle/usr/photon/bin/input-cfg
chmod 4775 target/qnx6/armle/usr/photon/bin/phlocale
chmod 4775 target/qnx6/armle/usr/photon/bin/launchmenu_notify
chmod 4775 target/qnx6/armle/usr/photon/bin/saver
chmod 4775 target/qnx6/armle/usr/photon/bin/phfont
chmod 4755 target/qnx6/armle/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/armle/usr/sbin/pppoed
chmod 4775 target/qnx6/armle/usr/sbin/dhcp.client
chmod 4775 target/qnx6/armle/usr/sbin/pppd
chmod 4775 target/qnx6/armle/sbin/pppoectl
chmod 4775 target/qnx6/armle/sbin/ifwatchd
chmod 4775 target/qnx6/shle/bin/login
chmod 4775 target/qnx6/shle/bin/su
chmod 4775 target/qnx6/shle/usr/bin/ping6
chmod 4775 target/qnx6/shle/usr/bin/lprq
chmod 4775 target/qnx6/shle/usr/bin/traceroute
chmod 4775 target/qnx6/shle/usr/bin/lpr
chmod 4775 target/qnx6/shle/usr/bin/rsh
chmod 4775 target/qnx6/shle/usr/bin/rcp
chmod 4775 target/qnx6/shle/usr/bin/crontab
chmod 4775 target/qnx6/shle/usr/bin/traceroute6
chmod 4775 target/qnx6/shle/usr/bin/rlogin
chmod 4775 target/qnx6/shle/usr/bin/ping
chmod 4775 target/qnx6/shle/usr/bin/newgrp
chmod 4775 target/qnx6/shle/usr/bin/netstat
chmod 4775 target/qnx6/shle/usr/bin/lprrm
chmod 4775 target/qnx6/shle/usr/bin/passwd
chmod 4775 target/qnx6/shle/usr/photon/bin/Photon
chmod 4775 target/qnx6/shle/usr/photon/bin/phshutdown
chmod 4775 target/qnx6/shle/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/shle/usr/photon/bin/phrelaycfg
chmod 4775 target/qnx6/shle/usr/photon/bin/phuser
chmod 4775 target/qnx6/shle/usr/photon/bin/input-cfg
chmod 4775 target/qnx6/shle/usr/photon/bin/phlocale
chmod 4775 target/qnx6/shle/usr/photon/bin/launchmenu_notify
chmod 4775 target/qnx6/shle/usr/photon/bin/saver
chmod 4775 target/qnx6/shle/usr/photon/bin/phfont
chmod 4755 target/qnx6/shle/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/shle/usr/sbin/pppoed
chmod 4775 target/qnx6/shle/usr/sbin/dhcp.client
chmod 4775 target/qnx6/shle/usr/sbin/pppd
chmod 4775 target/qnx6/shle/sbin/pppoectl
chmod 4775 target/qnx6/shle/sbin/ifwatchd
chmod 4775 target/qnx6/mipsle/bin/login
chmod 4775 target/qnx6/mipsle/bin/su
chmod 4775 target/qnx6/mipsle/usr/bin/ping6
chmod 4775 target/qnx6/mipsle/usr/bin/lprq
chmod 4775 target/qnx6/mipsle/usr/bin/traceroute
chmod 4775 target/qnx6/mipsle/usr/bin/lpr
chmod 4775 target/qnx6/mipsle/usr/bin/rsh
chmod 4775 target/qnx6/mipsle/usr/bin/rcp
chmod 4775 target/qnx6/mipsle/usr/bin/crontab
chmod 4775 target/qnx6/mipsle/usr/bin/traceroute6
chmod 4775 target/qnx6/mipsle/usr/bin/rlogin
chmod 4775 target/qnx6/mipsle/usr/bin/ping
chmod 4775 target/qnx6/mipsle/usr/bin/newgrp
chmod 4775 target/qnx6/mipsle/usr/bin/netstat
chmod 4775 target/qnx6/mipsle/usr/bin/lprrm
chmod 4775 target/qnx6/mipsle/usr/bin/passwd
chmod 4755 target/qnx6/mipsle/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/mipsle/usr/sbin/pppoed
chmod 4775 target/qnx6/mipsle/usr/sbin/dhcp.client
chmod 4775 target/qnx6/mipsle/usr/sbin/pppd
chmod 4775 target/qnx6/mipsle/sbin/pppoectl
chmod 4775 target/qnx6/mipsle/sbin/ifwatchd
chmod 4775 target/qnx6/mipsbe/bin/login
chmod 4775 target/qnx6/mipsbe/bin/su
chmod 4775 target/qnx6/mipsbe/usr/bin/ping6
chmod 4775 target/qnx6/mipsbe/usr/bin/lprq
chmod 4775 target/qnx6/mipsbe/usr/bin/traceroute
chmod 4775 target/qnx6/mipsbe/usr/bin/lpr
chmod 4775 target/qnx6/mipsbe/usr/bin/rsh
chmod 4775 target/qnx6/mipsbe/usr/bin/rcp
chmod 4775 target/qnx6/mipsbe/usr/bin/crontab
chmod 4775 target/qnx6/mipsbe/usr/bin/traceroute6
chmod 4775 target/qnx6/mipsbe/usr/bin/rlogin
chmod 4775 target/qnx6/mipsbe/usr/bin/ping
chmod 4775 target/qnx6/mipsbe/usr/bin/newgrp
chmod 4775 target/qnx6/mipsbe/usr/bin/netstat
chmod 4775 target/qnx6/mipsbe/usr/bin/lprrm
chmod 4775 target/qnx6/mipsbe/usr/bin/passwd
chmod 4755 target/qnx6/mipsbe/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/mipsbe/usr/sbin/pppoed
chmod 4775 target/qnx6/mipsbe/usr/sbin/dhcp.client
chmod 4775 target/qnx6/mipsbe/usr/sbin/pppd
chmod 4775 target/qnx6/mipsbe/sbin/pppoectl
chmod 4775 target/qnx6/mipsbe/sbin/ifwatchd
chmod 1755 host/linux/x86/usr/bin/qcc
chmod 1775 host/linux/x86/usr/bin/make
chmod 4755 host/linux/x86/usr/qde/eclipse/plugins/com.qnx.tools.ide.tftp_4.7.0.201006232051/os/linux/proxy
) >/tmp/qnxlink.log 2>&1
