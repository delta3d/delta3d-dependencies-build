cd `dirname $0`
export DYLD_LIBRARY_PATH=$PWD/../../dependencies/lib
./configure --disable-dependency-tracking --enable-osx-arch="i386 x86_64" --enable-osx-sdk="/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk" --prefix="$PWD/../../dependencies"
