# yue.nicholas@gmail.com

ADD_EXECUTABLE ( HalfTest
  main.cpp
  testArithmetic.cpp
  testBitPatterns.cpp
  testClassification.cpp
  testError.cpp
  testFunction.cpp
  testLimits.cpp
  testSize.cpp
  )
ADD_DEFINITIONS("-DOPENEXR_DLL")
TARGET_LINK_LIBRARIES ( HalfTest Half )

ADD_TEST ( TestHalf  HalfTest )
