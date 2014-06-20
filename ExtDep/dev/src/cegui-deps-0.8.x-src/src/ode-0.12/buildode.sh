#!/bin/bash

OLDCPPFLAGS=$CPPFLAGS
OLDLDFLAGS=$LDFLAGS

export CXX=/usr/bin/clang++
export CC=/usr/bin/clang
export CXXFLAGS="-std=c++11 -stdlib=libc++"

ARCHLIST="i386 x86_64"

LIPOLIST=""

for arch in ${ARCHLIST}; do


   echo $arch
   export LDFLAGS="$OLDLDFLAGS -arch $arch"
   export CPPFLAGS="$OLDCPPFLAGS -arch $arch"

   ./configure --disable-demos -prefix=$PWD/stage || exit 1

   make clean

   make install -j8
   
   mkdir stage/lib/$arch
   mv stage/lib/libode.a stage/lib/$arch
   
   LIPOLIST="$LIPOLIST stage/lib/$arch/libode.a"
done


lipo $LIPOLIST -create -o stage/lib/libode.a

rm -rf stage/inc
mv stage/include stage/inc   
   