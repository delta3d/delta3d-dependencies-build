rm -rf stage
mkdir -p stage/build/src/cppunit
mkdir -p stage/Frameworks/cppunit.framework/Versions/A/Headers

files=`find src/cppunit -name "*.cpp" -and -not -name Dll*`  

echo $files;

for token in $files; do 
   echo $token
   items="$items stage/build/$token.o"
   clang++ -Iinclude -arch i386 -arch x86_64 -O4 -fPIC -Wall -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7 -c $token -o stage/build/$token.o
done

cd include/cppunit
cp  *.h ../../stage/Frameworks/cppunit.framework/Versions/A/Headers
find . -depth 0 -type d -exec cp -R {} ../../stage/Frameworks/cppunit.framework/Versions/A/Headers \;
cd -

clang++ -dynamiclib -arch i386 -arch x86_64 -O4 -stdlib=libc++ -mmacosx-version-min=10.7 -single_module -install_name @executable_path/../Frameworks/cppunit.framework/Versions/A/cppunit -o stage/Frameworks/cppunit.framework/Versions/A/cppunit $items
ln -sf stage/Frameworks/cppunit.framework/Versions/A/cppunit stage/Frameworks/cppunit.framework
ln -sf stage/Frameworks/cppunit.framework/Versions/A/Headers stage/Frameworks/cppunit.framework

