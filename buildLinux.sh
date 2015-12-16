#!/bin/bash

cd `dirname $0`

echo boo
. ../basebuild.sh
echo who

cmake .  ${DEFAULT_CMAKE_OPTIONS} -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}" -DCMAKE_LD_FLAGS="${CMAKE_LD_FLAGS}" ${Boost_CMAKE_OPTIONS} -DCMAKE_INCLUDE_PATH:PATH=$EXT/include:$TBB_DIR/include -DCMAKE_LIBRARY_PATH:PATH=$TBB_DIR/lib -DDELTA3D_USE_EXTERNAL_OPENEXR=ON -DDELTA3D_BUILD_OPENVDB=OFF ${TBB_CMAKE_OPTIONS}  $@

LD_LIBRARY_PATH="$PWD/dependencies/lib/dynamic" make -j$PROCESSORS || exit 1

cd dependencies/include


cp -av AL cppunit xercesc ode nl.h gnelib.h gnelib cal3d OpenEXR openvdb pcre* $EXT/include

#mv $EXT/include/AL $EXT/include/OpenAL

cd ../lib/dynamic

cp -av libopenvdb* libHalf* libIlm* libIex* libImath* libNL.* libalut* libcal3d.* libcppunit.* libgne.* libode.* libxerces-c* libzlib.dylib $EXT/lib
