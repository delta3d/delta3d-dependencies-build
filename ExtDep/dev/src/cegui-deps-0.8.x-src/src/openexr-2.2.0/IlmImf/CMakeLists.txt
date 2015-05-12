# yue.nicholas@gmail.com

SET(CMAKE_INCLUDE_CURRENT_DIR 1)

ADD_EXECUTABLE ( b44ExpLogTable
  b44ExpLogTable.cpp
)

TARGET_LINK_LIBRARIES ( b44ExpLogTable
  Half
  Iex${ILMBASE_LIBSUFFIX}
  IlmThread${ILMBASE_LIBSUFFIX}
  ${PTHREAD_LIB}
)

ADD_CUSTOM_COMMAND (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/b44ExpLogTable.h
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/b44ExpLogTable > ${CMAKE_CURRENT_BINARY_DIR}/b44ExpLogTable.h
  DEPENDS b44ExpLogTable
)

ADD_EXECUTABLE ( dwaLookups
  dwaLookups.cpp
)

TARGET_LINK_LIBRARIES ( dwaLookups
  Half
  Iex${ILMBASE_LIBSUFFIX}
  IlmThread${ILMBASE_LIBSUFFIX}
  ${PTHREAD_LIB}
)

ADD_CUSTOM_COMMAND (TARGET dwaLookups POST_BUILD
  #OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/dwaLookups.h
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/dwaLookups > ${CMAKE_CURRENT_BINARY_DIR}/dwaLookups.h
  DEPENDS dwaLookups
)

SET ( ILMIMF_SRCS
  ImfAttribute.cpp
  ImfBoxAttribute.cpp
  ImfCRgbaFile.cpp
  ImfChannelList.cpp
  ImfChannelListAttribute.cpp
  ImfFloatAttribute.cpp
  ImfFrameBuffer.cpp
  ImfHeader.cpp
  ImfIO.cpp
  ImfInputFile.cpp
  ImfIntAttribute.cpp
  ImfLineOrderAttribute.cpp
  ImfMatrixAttribute.cpp
  ImfOpaqueAttribute.cpp
  ImfOutputFile.cpp
  ImfRgbaFile.cpp
  ImfStringAttribute.cpp
  ImfVecAttribute.cpp
  ImfHuf.cpp
  ImfThreading.cpp
  ImfWav.cpp
  ImfLut.cpp
  ImfCompressor.cpp
  ImfRleCompressor.cpp
  ImfZipCompressor.cpp
  ImfPizCompressor.cpp
  ImfB44Compressor.cpp
  ImfDwaCompressor.cpp
  ImfMisc.cpp
  ImfCompressionAttribute.cpp
  ImfDoubleAttribute.cpp
  ImfConvert.cpp
  ImfPreviewImage.cpp
  ImfPreviewImageAttribute.cpp
  ImfVersion.cpp
  ImfChromaticities.cpp
  ImfChromaticitiesAttribute.cpp
  ImfKeyCode.cpp
  ImfKeyCodeAttribute.cpp
  ImfTimeCode.cpp
  ImfTimeCodeAttribute.cpp
  ImfRational.cpp
  ImfRationalAttribute.cpp
  ImfFramesPerSecond.cpp
  ImfStandardAttributes.cpp
  ImfStdIO.cpp
  ImfEnvmap.cpp
  ImfEnvmapAttribute.cpp
  ImfScanLineInputFile.cpp
  ImfTiledInputFile.cpp
  ImfTiledMisc.cpp
  ImfTiledOutputFile.cpp
  ImfTiledRgbaFile.cpp
  ImfTileDescriptionAttribute.cpp
  ImfTileOffsets.cpp
  ImfRgbaYca.cpp
  ImfPxr24Compressor.cpp
  ImfTestFile.cpp
  ImfStringVectorAttribute.cpp
  ImfMultiView.cpp
  ImfAcesFile.cpp
  ImfMultiPartOutputFile.cpp
  ImfGenericOutputFile.cpp
  ImfOutputPartData.cpp
  ImfMultiPartInputFile.cpp
  ImfGenericInputFile.cpp
  ImfPartType.cpp
  ImfInputPartData.cpp
  ImfOutputPart.cpp
  ImfTiledOutputPart.cpp
  ImfInputPart.cpp
  ImfTiledInputPart.cpp
  ImfDeepScanLineInputPart.cpp
  ImfDeepScanLineOutputPart.cpp
  ImfDeepScanLineInputFile.cpp
  ImfDeepScanLineOutputFile.cpp
  ImfDeepTiledInputPart.cpp
  ImfDeepTiledOutputPart.cpp
  ImfDeepTiledInputFile.cpp
  ImfDeepTiledOutputFile.cpp
  ImfDeepFrameBuffer.cpp
  ImfDeepCompositing.cpp
  ImfCompositeDeepScanLine.cpp
  ImfDeepImageStateAttribute.cpp
  ImfFastHuf.cpp
  ImfFloatVectorAttribute.cpp
  ImfRle.cpp
  ImfSystemSpecific.cpp
  ImfZip.cpp
)

cegui_add_library(IlmImf ILMIMF_SRCS NONE)

if (WIN32)
    set_property(TARGET IlmImf APPEND PROPERTY
       COMPILE_DEFINITIONS "ILMIMF_EXPORTS")
endif ()


Set(HEADERS
  ImfForward.h
  ImfExport.h
  ImfAttribute.h
  ImfBoxAttribute.h
  ImfCRgbaFile.h
  ImfChannelList.h
  ImfChannelListAttribute.h
  ImfCompressionAttribute.h
  ImfDoubleAttribute.h
  ImfFloatAttribute.h
  ImfFrameBuffer.h
  ImfHeader.h
  ImfIO.h
  ImfInputFile.h
  ImfIntAttribute.h
  ImfLineOrderAttribute.h
  ImfMatrixAttribute.h
  ImfOpaqueAttribute.h
  ImfOutputFile.h
  ImfRgbaFile.h
  ImfStringAttribute.h
  ImfVecAttribute.h
  ImfHuf.h
  ImfWav.h
  ImfLut.h
  ImfArray.h
  ImfCompression.h
  ImfLineOrder.h
  ImfName.h
  ImfPixelType.h
  ImfVersion.h
  ImfXdr.h
  ImfConvert.h
  ImfPreviewImage.h
  ImfPreviewImageAttribute.h
  ImfChromaticities.h
  ImfChromaticitiesAttribute.h
  ImfKeyCode.h
  ImfKeyCodeAttribute.h
  ImfTimeCode.h
  ImfTimeCodeAttribute.h
  ImfRational.h
  ImfRationalAttribute.h
  ImfFramesPerSecond.h
  ImfStandardAttributes.h
  ImfEnvmap.h
  ImfEnvmapAttribute.h
  ImfInt64.h
  ImfRgba.h
  ImfTileDescription.h
  ImfTileDescriptionAttribute.h
  ImfTiledInputFile.h
  ImfTiledOutputFile.h
  ImfTiledRgbaFile.h
  ImfRgbaYca.h
  ImfTestFile.h
  ImfThreading.h
  ImfB44Compressor.h
  ImfStringVectorAttribute.h
  ImfMultiView.h
  ImfAcesFile.h
  ImfMultiPartOutputFile.h
  ImfGenericOutputFile.h
  ImfMultiPartInputFile.h
  ImfGenericInputFile.h
  ImfPartType.h
  ImfPartHelper.h
  ImfOutputPart.h
  ImfTiledOutputPart.h
  ImfInputPart.h
  ImfTiledInputPart.h
  ImfDeepScanLineOutputFile.h
  ImfDeepScanLineOutputPart.h
  ImfDeepScanLineInputFile.h
  ImfDeepScanLineInputPart.h
  ImfDeepTiledInputFile.h
  ImfDeepTiledInputPart.h
  ImfDeepTiledOutputFile.h
  ImfDeepTiledOutputPart.h
  ImfDeepFrameBuffer.h
  ImfDeepCompositing.h
  ImfCompositeDeepScanLine.h
  ImfNamespace.h
  ImfMisc.h
  ImfDeepImageState.h
  ImfDeepImageStateAttribute.h
  ImfFloatVectorAttribute.h
)

INSTALL ( FILES ${HEADERS}
  DESTINATION
  include/OpenEXR
)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET IlmImf POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
       "${CMAKE_BINARY_DIR}/dependencies/include/OpenEXR")
endforeach()


TARGET_LINK_LIBRARIES ( IlmImf 
  Half 
  Iex${ILMBASE_LIBSUFFIX}
  Imath${ILMBASE_LIBSUFFIX}
  IlmThread${ILMBASE_LIBSUFFIX}
  ${PTHREAD_LIB} 
  #${ZLIB_LIBRARIES}
  zlib
)

ADD_DEPENDENCIES ( IlmImf b44ExpLogTable )

SET_SOURCE_FILES_PROPERTIES (
  ImfB44Compressor.cpp
  PROPERTIES
  OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/b44ExpLogTable.h
)

ADD_DEPENDENCIES ( IlmImf dwaLookups )
ADD_DEPENDENCIES ( IlmImf_static dwaLookups )

SET_SOURCE_FILES_PROPERTIES (
  ImfDwaCompressor.cpp
  PROPERTIES
  OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/dwaLookups.h
)

# Libraries

INSTALL ( TARGETS
  IlmImf
  DESTINATION
  ${CMAKE_INSTALL_PREFIX}/lib
)
