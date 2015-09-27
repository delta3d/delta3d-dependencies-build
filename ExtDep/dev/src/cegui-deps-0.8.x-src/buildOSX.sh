#!/bin/bash

EXT=$DEV/ext

source $DEV/basebuild.sh

cd `dirname $0`

if ! cp -av $DEV/tbb43_20150316oss_osx/lib/libc++/*.dylib $EXT/lib; then
   echo "Error copying tbb.  Check path"
   exit 1
fi

pushd $EXT/lib
for token in *tbb*.dylib; do 
	install_name_tool -id @executable_path/../lib/$token $token;
        for tokenInner in *tbb*.dylib; do 
   		install_name_tool -change $tokenInner @executable_path/../lib/$tokenInner $token;
   	done
done
popd

cmake .  ${DEFAULT_CMAKE_OPTIONS} -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}" -DCMAKE_LD_FLAGS="${CMAKE_LD_FLAGS}" ${Boost_CMAKE_OPTIONS} -DCEGUI_BUILD_XERCES=ON -DCMAKE_INCLUDE_PATH:PATH=$EXT/include:$TBB_DIR/include -DCMAKE_LIBRARY_PATH:PATH=$TBB_DIR/lib ${TBB_CMAKE_OPTIONS}  $@

PROCESSORS=$(sysctl hw.ncpu | awk '{print $2}')
DYLD_LIBRARY_PATH="$PWD/dependencies/lib/dynamic" make -j$PROCESSORS || exit 1

cd dependencies/include


cp -av AL cppunit xercesc ode nl.h gnelib.h gnelib cal3d OpenEXR openvdb $EXT/include

mv $EXT/include/AL $EXT/include/OpenAL

cd ../lib/dynamic

cp -av libopenvdb* libHalf* libIlm* libIex* libImath* libNL.* libalut* libcal3d.* libcppunit.* libgne.* libode.* libxerces-c* libzlib.dylib $EXT/lib

cd ..

cp -av static/libexpat.a static/libfreetype.a static/libglew.a static/libglfw.a static/libjpeg.a static/liblibpng.a static/liblua.a static/libpcre.a static/libSILLY.a  static/libtoluapp.a dynamic/libxerces-c* dynamic/libzlib.* $EXT/src/CEGUI-0.7.9/projects/Xcode/dependencies/lib
