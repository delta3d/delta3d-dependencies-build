CC=/usr/bin/clang
CXX=/usr/bin/clang++

CXXFLAGS="-std=c++11 -stdlib=libc++"

make clean
ARCH=i386 make -j2 

mkdir i386
mkdir x86_64

cp lib/mingw/libgne.a ./i386

make clean
ARCH=x86_64 make -j2 

cp lib/mingw/libgne.a ./x86_64


lipo ./i386/libgne.a ./x86_64/libgne.a -create -o libgne.a