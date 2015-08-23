# Install script for directory: /Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfForward.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfExport.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfBoxAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfCRgbaFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfChannelList.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfChannelListAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfCompressionAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDoubleAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfFloatAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfFrameBuffer.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfHeader.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfIO.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfInputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfIntAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfLineOrderAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfMatrixAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfOpaqueAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfOutputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfRgbaFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfStringAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfVecAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfHuf.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfWav.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfLut.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfArray.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfCompression.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfLineOrder.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfName.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfPixelType.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfVersion.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfXdr.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfConvert.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfPreviewImage.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfPreviewImageAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfChromaticities.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfChromaticitiesAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfKeyCode.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfKeyCodeAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTimeCode.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTimeCodeAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfRational.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfRationalAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfFramesPerSecond.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfStandardAttributes.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfEnvmap.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfEnvmapAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfInt64.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfRgba.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTileDescription.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTileDescriptionAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTiledInputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTiledOutputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTiledRgbaFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfRgbaYca.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTestFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfThreading.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfB44Compressor.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfStringVectorAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfMultiView.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfAcesFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfMultiPartOutputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfGenericOutputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfMultiPartInputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfGenericInputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfPartType.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfPartHelper.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfOutputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTiledOutputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfInputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfTiledInputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepScanLineOutputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepScanLineOutputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepScanLineInputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepScanLineInputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepTiledInputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepTiledInputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepTiledOutputFile.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepTiledOutputPart.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepFrameBuffer.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepCompositing.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfCompositeDeepScanLine.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfNamespace.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfMisc.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepImageState.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfDeepImageStateAttribute.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/ImfFloatVectorAttribute.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libIlmImf.22.0.0.dylib;/usr/local/lib/libIlmImf.22.dylib;/usr/local/lib/libIlmImf.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libIlmImf.22.0.0.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libIlmImf.22.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libIlmImf.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}/usr/local/lib/libIlmImf.22.0.0.dylib"
      "$ENV{DESTDIR}/usr/local/lib/libIlmImf.22.dylib"
      "$ENV{DESTDIR}/usr/local/lib/libIlmImf.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

