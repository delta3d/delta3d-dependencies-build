# yue.nicholas@gmail.com

IF(BUILD_SHARED_LIBS AND WIN32)
    ADD_DEFINITIONS("-DOPENEXR_DLL")
ENDIF()

ADD_EXECUTABLE ( IlmImfExamples
  drawImage.cpp
  generalInterfaceExamples.cpp
  generalInterfaceTiledExamples.cpp
  lowLevelIoExamples.cpp
  main.cpp
  previewImageExamples.cpp
  rgbaInterfaceExamples.cpp
  rgbaInterfaceTiledExamples.cpp
 )


TARGET_LINK_LIBRARIES ( IlmImfExamples 
        IlmImf
        Half 
        Iex${ILMBASE_LIBSUFFIX}
        Imath${ILMBASE_LIBSUFFIX}
        IlmThread${ILMBASE_LIBSUFFIX}
        ${PTHREAD_LIB} ${ZLIB_LIBRARIES}
        )
  
