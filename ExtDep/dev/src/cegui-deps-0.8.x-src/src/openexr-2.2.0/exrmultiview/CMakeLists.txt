# yue.nicholas@gmail.com

IF(BUILD_SHARED_LIBS AND WIN32)
    ADD_DEFINITIONS("-DOPENEXR_DLL")
ENDIF()

ADD_EXECUTABLE ( exrmultiview
  makeMultiView.cpp
  main.cpp
  Image.cpp
)

TARGET_LINK_LIBRARIES ( exrmultiview
  IlmImf
  Half
  Imath${ILMBASE_LIBSUFFIX}
  Iex${ILMBASE_LIBSUFFIX}
  IlmThread${ILMBASE_LIBSUFFIX}
  ${PTHREAD_LIB}
  ${ZLIB_LIBRARIES}
)

INSTALL ( TARGETS
  exrmultiview
  DESTINATION
  ${CMAKE_INSTALL_PREFIX}/bin
)
