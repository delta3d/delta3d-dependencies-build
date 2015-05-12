#!/bin/bash

cd `dirname $0`

EXT=$DEV/ext

export CMAKE_BUILD_TYPE=Release

cmake . -DCEGUI_BUILD_XERCES=ON -DCMAKE_INCLUDE_PATH:PATH=$EXT/include -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_OSX_ARCHITECTURES:STRING='i386;x86_64' -DCMAKE_OSX_DEPLOYMENT_TARGET:STRING=10.7 -DCMAKE_CXX_FLAGS="-stdlib=libc++"  $@

PROCESSORS=$(sysctl hw.ncpu | awk '{print $2}')
DYLD_LIBRARY_PATH="$DYLD_LIBRARY_PATH:$PWD/dependencies/lib/dynamic" make -j$PROCESSORS || exit 1

cd dependencies/include


cp -av AL cppunit xercesc ode nl.h gnelib.h gnelib cal3d OpenEXR $EXT/include

cd ../lib/dynamic

cp -av libHalf* libIlm* libIex* libImath* libNL.* libalut* libcal3d.* libcppunit.* libgne.* libode.* libxerces-c* libzlib.dylib $EXT/lib

cd ..

cp -av static/libexpat.a static/libfreetype.a static/libglew.a static/libglfw.a static/libjpeg.a static/liblibpng.a static/liblua.a static/libpcre.a static/libSILLY.a  static/libtoluapp.a dynamic/libxerces-c* dynamic/libzlib.* $EXT/src/CEGUI-0.7.9/projects/Xcode/dependencies/lib
