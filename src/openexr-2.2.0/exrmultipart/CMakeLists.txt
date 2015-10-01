# yue.nicholas@gmail.com

IF(BUILD_SHARED_LIBS AND WIN32)
    ADD_DEFINITIONS("-DOPENEXR_DLL")
ENDIF()

ADD_EXECUTABLE ( exrmultipart
  exrmultipart.cpp
)

TARGET_LINK_LIBRARIES ( exrmultipart
  IlmImf
  IlmThread${ILMBASE_LIBSUFFIX}
  Iex${ILMBASE_LIBSUFFIX}
  Half
  ${PTHREAD_LIB}
  ${ZLIB_LIBRARIES}
)

INSTALL ( TARGETS
  exrmultipart
  DESTINATION
  ${CMAKE_INSTALL_PREFIX}/bin
)
