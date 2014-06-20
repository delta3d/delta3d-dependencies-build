#!/bin/sh
TESTLIBTOOLIZE="glibtoolize libtoolize"

LIBTOOLIZEFOUND="0"

aclocal-1.11 --version > /dev/null 2> /dev/null || {
    echo "error: aclocal not found"
    exit 1
}
automake-1.11 --version > /dev/null 2> /dev/null || {
    echo "error: automake not found"
    exit 1
}

for i in $TESTLIBTOOLIZE; do
	if which $i > /dev/null 2>&1; then
		LIBTOOLIZE=$i
		LIBTOOLIZEFOUND="1"
		break
	fi
done

if [ "$LIBTOOLIZEFOUND" = "0" ]; then
	echo "$0: need libtoolize tool to build cppunit" >&2
	exit 1
fi

amcheck=`automake-1.11 --version | grep 'automake (GNU automake) 1.5'`
if test "x$amcheck" = "xautomake (GNU automake) 1.5"; then
    echo "warning: you appear to be using automake 1.5"
    echo "         this version has a bug - GNUmakefile.am dependencies are not generated"
fi

rm -rf autom4te*.cache

$LIBTOOLIZE --force --copy || {
    echo "error: libtoolize failed"
    exit 1
}
aclocal-1.11 $ACLOCAL_FLAGS -I config || {
    echo "error: aclocal $ACLOCAL_FLAGS failed"
    exit 1
}
autoheader || {
    echo "error: autoheader failed"
    exit 1
}
automake-1.11 -a -c --foreign || {
    echo "warning: automake failed"
}
autoconf || {
    echo "error: autoconf failed"
    exit 1
}
