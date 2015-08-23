# Install script for directory: /Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libIlmThread-2_2.12.0.0.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libIlmThread-2_2.12.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libIlmThread-2_2.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread-2_2.12.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread-2_2.12.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread-2_2.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/static/libIlmThread.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread.a")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/IlmThreadPool.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/IlmThread.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/IlmThreadSemaphore.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/IlmThreadMutex.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/IlmThreadNamespace.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/IlmThreadExport.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/IlmThreadForward.h"
    )
endif()

