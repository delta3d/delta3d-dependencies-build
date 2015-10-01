# yue.nicholas@gmail.com

IF(BUILD_SHARED_LIBS AND WIN32)
    ADD_DEFINITIONS("-DOPENEXR_DLL")
ENDIF()

ADD_EXECUTABLE ( exrenvmap
  makeLatLongMap.cpp
  readInputImage.cpp
  resizeImage.cpp
  makeCubeMap.cpp
  main.cpp
  blurImage.cpp
  EnvmapImage.cpp
)

TARGET_LINK_LIBRARIES ( exrenvmap
  IlmImf
  IlmThread${ILMBASE_LIBSUFFIX}
  Iex${ILMBASE_LIBSUFFIX}
  Half
  ${PTHREAD_LIB}
  ${ZLIB_LIBRARIES}
)

INSTALL ( TARGETS
  exrenvmap
  DESTINATION
  ${CMAKE_INSTALL_PREFIX}/bin
)
