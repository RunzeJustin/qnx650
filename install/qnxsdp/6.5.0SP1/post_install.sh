#!/bin/sh

(
BASEDIR=$1
if test ! -r $BASEDIR/host/linux/x86/usr/bin; then
    test -r $BASEDIR/host || mkdir $BASEDIR/host
    test -r $BASEDIR/host/linux || mkdir $BASEDIR/host/linux
    test -r $BASEDIR/host/linux/x86 || mkdir $BASEDIR/host/linux/x86
    test -r $BASEDIR/host/linux/x86/usr || mkdir $BASEDIR/host/linux/x86/usr
    test -r $BASEDIR/host/linux/x86/usr/bin || mkdir $BASEDIR/host/linux/x86/usr/bin
fi
if test -d $BASEDIR/host/linux/x86/usr/bin; then
   cd $BASEDIR/host/linux/x86/usr/bin
   ln -s -f mkxfs mketfs
ln -s -f mkxfs mkefs
ln -s -f mkxfs mkifs
else
   echo "Could not change to $BASEDIR/host/linux/x86/usr/bin"
fi

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

if test ! -r $BASEDIR/target/qnx6/armle-v7/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/lib || mkdir $BASEDIR/target/qnx6/armle-v7/lib
fi
if test -d $BASEDIR/target/qnx6/armle-v7/lib; then
   cd $BASEDIR/target/qnx6/armle-v7/lib
   ln -s -f libcam.so.2 libcam.so
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libc.so.3 libc.so
ln -s -f libasound.so.2 libasound.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libm.so.2 libm.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libpps.so.1 libpps.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle-v7/lib"
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
   ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f bzip2 bzcat
ln -s -f bzgrep bzegrep
ln -s -f bzdiff bzcmp
ln -s -f bzmore bzless
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
   ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libcrypto.so.2 libcrypto.so
ln -s -f libbz2.so.1 libbz2.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libssl.so.2 libssl.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libham.so.2 libham.so
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libgf.so.1 libgf.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libz.so.2 libz.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f librcheck.so.1 librcheck.so
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

if test ! -r $BASEDIR/target/qnx6/armle-v7/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle-v7 || mkdir $BASEDIR/target/qnx6/armle-v7
    test -r $BASEDIR/target/qnx6/armle-v7/usr || mkdir $BASEDIR/target/qnx6/armle-v7/usr
    test -r $BASEDIR/target/qnx6/armle-v7/usr/sbin || mkdir $BASEDIR/target/qnx6/armle-v7/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/armle-v7/usr/sbin; then
   cd $BASEDIR/target/qnx6/armle-v7/usr/sbin
   ln -s -f named lwresd
ln -s -f named-checkzone named-compilezone
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
   ln -s -f gunzip uncompress
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
   ln -s -f libcam.so.2 libcam.so
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libc.so.3 libc.so
ln -s -f libasound.so.2 libasound.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libm-vfp.so.2 libm-vfp.so
ln -s -f libm.so.2 libm.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libpps.so.1 libpps.so
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/lib"
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
   ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f bzip2 bzcat
ln -s -f bzgrep bzegrep
ln -s -f bzdiff bzcmp
ln -s -f bzmore bzless
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
   ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libcrypto.so.2 libcrypto.so
ln -s -f libbz2.so.1 libbz2.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libssl.so.2 libssl.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libham.so.2 libham.so
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libgf.so.1 libgf.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libz.so.2 libz.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f librcheck.so.1 librcheck.so
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

if test ! -r $BASEDIR/target/qnx6/armle/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/armle || mkdir $BASEDIR/target/qnx6/armle
    test -r $BASEDIR/target/qnx6/armle/usr || mkdir $BASEDIR/target/qnx6/armle/usr
    test -r $BASEDIR/target/qnx6/armle/usr/sbin || mkdir $BASEDIR/target/qnx6/armle/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/armle/usr/sbin; then
   cd $BASEDIR/target/qnx6/armle/usr/sbin
   ln -s -f named lwresd
ln -s -f named-checkzone named-compilezone
else
   echo "Could not change to $BASEDIR/target/qnx6/armle/usr/sbin"
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

if test ! -r $BASEDIR/target/qnx6/ppcbe-spe/lib; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe-spe || mkdir $BASEDIR/target/qnx6/ppcbe-spe
    test -r $BASEDIR/target/qnx6/ppcbe-spe/lib || mkdir $BASEDIR/target/qnx6/ppcbe-spe/lib
fi
if test -d $BASEDIR/target/qnx6/ppcbe-spe/lib; then
   cd $BASEDIR/target/qnx6/ppcbe-spe/lib
   ln -s -f libcam.so.2 libcam.so
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libc.so.3 libc.so
ln -s -f libasound.so.2 libasound.so
ln -s -f libm.so.2 libm.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libpps.so.1 libpps.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe-spe/lib"
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
   ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f bzip2 bzcat
ln -s -f bzgrep bzegrep
ln -s -f bzdiff bzcmp
ln -s -f bzmore bzless
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
   ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libcrypto.so.2 libcrypto.so
ln -s -f libbz2.so.1 libbz2.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libssl.so.2 libssl.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libham.so.2 libham.so
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libz.so.2 libz.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f librcheck.so.1 librcheck.so
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
   ln -s -f named lwresd
ln -s -f named-checkzone named-compilezone
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
   ln -s -f gunzip uncompress
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
   ln -s -f libcam.so.2 libcam.so
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libc.so.3 libc.so
ln -s -f libasound.so.2 libasound.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libm.so.2 libm.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libpps.so.1 libpps.so
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/lib"
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
   ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f bzip2 bzcat
ln -s -f bzgrep bzegrep
ln -s -f bzdiff bzcmp
ln -s -f bzmore bzless
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
   ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libcrypto.so.2 libcrypto.so
ln -s -f libbz2.so.1 libbz2.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libssl.so.2 libssl.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libham.so.2 libham.so
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libgf.so.1 libgf.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libz.so.2 libz.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f librcheck.so.1 librcheck.so
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

if test ! -r $BASEDIR/target/qnx6/ppcbe/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/ppcbe || mkdir $BASEDIR/target/qnx6/ppcbe
    test -r $BASEDIR/target/qnx6/ppcbe/usr || mkdir $BASEDIR/target/qnx6/ppcbe/usr
    test -r $BASEDIR/target/qnx6/ppcbe/usr/sbin || mkdir $BASEDIR/target/qnx6/ppcbe/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/ppcbe/usr/sbin; then
   cd $BASEDIR/target/qnx6/ppcbe/usr/sbin
   ln -s -f named lwresd
ln -s -f named-checkzone named-compilezone
else
   echo "Could not change to $BASEDIR/target/qnx6/ppcbe/usr/sbin"
fi

if test ! -r $BASEDIR/target/qnx6/usr/include; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/usr || mkdir $BASEDIR/target/qnx6/usr
    test -r $BASEDIR/target/qnx6/usr/include || mkdir $BASEDIR/target/qnx6/usr/include
fi
if test -d $BASEDIR/target/qnx6/usr/include; then
   cd $BASEDIR/target/qnx6/usr/include
   ln -s -f mk/phapps.mk phapps.mk
ln -s -f sys/md5.h md5.h
ln -s -f mk/recurse.mk recurse.mk
ln -s -f sys/queue.h queue.h
ln -s -f sys/poll.h poll.h
ln -s -f mk/ab.mk ab.mk
ln -s -f mk/buildlist.mk buildlist.mk
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
   ln -s -f gunzip uncompress
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
   ln -s -f libcam.so.2 libcam.so
ln -s -f libhiddi.so.1 libhiddi.so
ln -s -f libc.so.3 libc.so
ln -s -f libasound.so.2 libasound.so
ln -s -f libimg.so.1 libimg.so
ln -s -f libm.so.2 libm.so
ln -s -f libsocket.so.3 libsocket.so
ln -s -f libwlconfig.so.1 libwlconfig.so
ln -s -f libusbdi.so.2 libusbdi.so
ln -s -f libpps.so.1 libpps.so
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/lib"
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
   ln -s -f bzgrep bzfgrep
ln -s -f bzip2 bunzip2
ln -s -f bzip2 bzcat
ln -s -f bzgrep bzegrep
ln -s -f bzdiff bzcmp
ln -s -f ../../usr/photon/bin/inputtrap inputtrap
ln -s -f bzmore bzless
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
   ln -s -f ../../lib/libc.so.3 ldqnx.so.2
ln -s -f libcrypto.so.2 libcrypto.so
ln -s -f libbz2.so.1 libbz2.so
ln -s -f libbacktrace.so.1 libbacktrace.so
ln -s -f libssl.so.2 libssl.so
ln -s -f libqdb_cldr.so.1 libqdb_cldr.so
ln -s -f libnbutil.so.1 libnbutil.so
ln -s -f malloc_g/libmallocS.a libmalloc_gS.a
ln -s -f libham.so.2 libham.so
ln -s -f libsqlite3.so.1 libsqlite3.so
ln -s -f libqdb.so.1 libqdb.so
ln -s -f libgf.so.1 libgf.so
ln -s -f libAp.so.3 libAp.so
ln -s -f libmalloc.so.2 libmalloc.so
ln -s -f libz.so.2 libz.so
ln -s -f libcurl.so.2 libcurl.so
ln -s -f malloc_g/libmalloc.so libmalloc_g.so
ln -s -f librcheck.so.1 librcheck.so
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

if test ! -r $BASEDIR/target/qnx6/x86/usr/sbin; then
    test -r $BASEDIR/target || mkdir $BASEDIR/target
    test -r $BASEDIR/target/qnx6 || mkdir $BASEDIR/target/qnx6
    test -r $BASEDIR/target/qnx6/x86 || mkdir $BASEDIR/target/qnx6/x86
    test -r $BASEDIR/target/qnx6/x86/usr || mkdir $BASEDIR/target/qnx6/x86/usr
    test -r $BASEDIR/target/qnx6/x86/usr/sbin || mkdir $BASEDIR/target/qnx6/x86/usr/sbin
fi
if test -d $BASEDIR/target/qnx6/x86/usr/sbin; then
   cd $BASEDIR/target/qnx6/x86/usr/sbin
   ln -s -f named lwresd
ln -s -f named-checkzone named-compilezone
else
   echo "Could not change to $BASEDIR/target/qnx6/x86/usr/sbin"
fi

cd $BASEDIR
chmod 4775 target/qnx6/armle-v7/bin/su
chmod 4775 target/qnx6/armle-v7/sbin/ifwatchd
chmod 4775 target/qnx6/armle-v7/sbin/pppoectl
chmod 4775 target/qnx6/armle-v7/usr/bin/netstat
chmod 4775 target/qnx6/armle-v7/usr/bin/ping
chmod 4775 target/qnx6/armle-v7/usr/bin/ping6
chmod 4775 target/qnx6/armle-v7/usr/bin/traceroute
chmod 4775 target/qnx6/armle-v7/usr/bin/traceroute6
chmod 4775 target/qnx6/armle-v7/usr/sbin/dhcp.client
chmod 4775 target/qnx6/armle-v7/usr/sbin/pppd
chmod 4775 target/qnx6/armle-v7/usr/sbin/pppoed
chmod 4755 target/qnx6/armle-v7/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/armle-v7/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/armle/bin/su
chmod 4775 target/qnx6/armle/sbin/ifwatchd
chmod 4775 target/qnx6/armle/sbin/pppoectl
chmod 4775 target/qnx6/armle/usr/bin/netstat
chmod 4775 target/qnx6/armle/usr/bin/ping
chmod 4775 target/qnx6/armle/usr/bin/ping6
chmod 4775 target/qnx6/armle/usr/bin/traceroute
chmod 4775 target/qnx6/armle/usr/bin/traceroute6
chmod 4775 target/qnx6/armle/usr/sbin/dhcp.client
chmod 4775 target/qnx6/armle/usr/sbin/pppd
chmod 4775 target/qnx6/armle/usr/sbin/pppoed
chmod 4755 target/qnx6/armle/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/armle/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/ppcbe/bin/su
chmod 4775 target/qnx6/ppcbe/sbin/ifwatchd
chmod 4775 target/qnx6/ppcbe/sbin/pppoectl
chmod 4775 target/qnx6/ppcbe/usr/bin/netstat
chmod 4775 target/qnx6/ppcbe/usr/bin/ping
chmod 4775 target/qnx6/ppcbe/usr/bin/ping6
chmod 4775 target/qnx6/ppcbe/usr/bin/traceroute
chmod 4775 target/qnx6/ppcbe/usr/bin/traceroute6
chmod 4775 target/qnx6/ppcbe/usr/sbin/dhcp.client
chmod 4775 target/qnx6/ppcbe/usr/sbin/pppd
chmod 4775 target/qnx6/ppcbe/usr/sbin/pppoed
chmod 4755 target/qnx6/ppcbe/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/ppcbe/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/ppcbe-spe/bin/su
chmod 4775 target/qnx6/ppcbe-spe/sbin/ifwatchd
chmod 4775 target/qnx6/ppcbe-spe/sbin/pppoectl
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/netstat
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/ping
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/ping6
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/traceroute
chmod 4775 target/qnx6/ppcbe-spe/usr/bin/traceroute6
chmod 4775 target/qnx6/ppcbe-spe/usr/sbin/dhcp.client
chmod 4775 target/qnx6/ppcbe-spe/usr/sbin/pppd
chmod 4775 target/qnx6/ppcbe-spe/usr/sbin/pppoed
chmod 4755 target/qnx6/ppcbe-spe/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/x86/bin/su
chmod 4775 target/qnx6/x86/sbin/ifwatchd
chmod 4775 target/qnx6/x86/sbin/pppoectl
chmod 4775 target/qnx6/x86/usr/bin/netstat
chmod 4775 target/qnx6/x86/usr/bin/ping
chmod 4775 target/qnx6/x86/usr/bin/ping6
chmod 4775 target/qnx6/x86/usr/bin/traceroute
chmod 4775 target/qnx6/x86/usr/bin/traceroute6
chmod 4775 target/qnx6/x86/usr/sbin/dhcp.client
chmod 4775 target/qnx6/x86/usr/sbin/pppd
chmod 4775 target/qnx6/x86/usr/sbin/pppoed
chmod 4755 target/qnx6/x86/usr/libexec/ssh-keysign
chmod 4775 target/qnx6/x86/usr/photon/bin/io-graphics
chmod 4775 target/qnx6/x86/usr/photon/bin/inputtrap
) >/tmp/qnxlink.log 2>&1
