
# IlmImfUtilTest

LINK_DIRECTORIES ( ${CMAKE_CURRENT_BINARY_DIR}/../IlmImf )

IF(BUILD_SHARED_LIBS AND WIN32)
    ADD_DEFINITIONS("-DOPENEXR_DLL")
ENDIF()

ADD_EXECUTABLE ( IlmImfUtilTest
  main.cpp
  testFlatImage.cpp
  testDeepImage.cpp
  testIO.cpp
 )


ADD_TEST ( TestIlmImfUtil IlmImfUtilTest )
TARGET_LINK_LIBRARIES ( IlmImfUtilTest 
        IlmImfUtil
        IlmImf  
        Half 
        Iex${ILMBASE_LIBSUFFIX}
        Imath${ILMBASE_LIBSUFFIX}
        IlmThread${ILMBASE_LIBSUFFIX}
        ${PTHREAD_LIB} ${ZLIB_LIBRARIES}
        )

