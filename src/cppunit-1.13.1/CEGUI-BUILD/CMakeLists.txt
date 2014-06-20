set(DEPNAME cppunit)

set(SOURCES 
../src/cppunit/AdditionalMessage.cpp
../src/cppunit/Asserter.cpp
../src/cppunit/BeOsDynamicLibraryManager.cpp
../src/cppunit/BriefTestProgressListener.cpp
../src/cppunit/CompilerOutputter.cpp
../src/cppunit/DefaultProtector.cpp
#../src/cppunit/DllMain.cpp
../src/cppunit/DynamicLibraryManager.cpp
../src/cppunit/DynamicLibraryManagerException.cpp
../src/cppunit/Exception.cpp
../src/cppunit/Message.cpp
../src/cppunit/PlugInManager.cpp
../src/cppunit/PlugInParameters.cpp
../src/cppunit/Protector.cpp
../src/cppunit/ProtectorChain.cpp
../src/cppunit/RepeatedTest.cpp
../src/cppunit/ShlDynamicLibraryManager.cpp
../src/cppunit/SourceLine.cpp
../src/cppunit/StringTools.cpp
../src/cppunit/SynchronizedObject.cpp
../src/cppunit/Test.cpp
../src/cppunit/TestAssert.cpp
../src/cppunit/TestCase.cpp
../src/cppunit/TestCaseDecorator.cpp
../src/cppunit/TestComposite.cpp
../src/cppunit/TestDecorator.cpp
../src/cppunit/TestFactoryRegistry.cpp
../src/cppunit/TestFailure.cpp
../src/cppunit/TestLeaf.cpp
../src/cppunit/TestNamer.cpp
../src/cppunit/TestPath.cpp
../src/cppunit/TestPlugInDefaultImpl.cpp
../src/cppunit/TestResult.cpp
../src/cppunit/TestResultCollector.cpp
../src/cppunit/TestRunner.cpp
../src/cppunit/TestSetUp.cpp
../src/cppunit/TestSuccessListener.cpp
../src/cppunit/TestSuite.cpp
../src/cppunit/TestSuiteBuilderContext.cpp
../src/cppunit/TextOutputter.cpp
../src/cppunit/TextTestProgressListener.cpp
../src/cppunit/TextTestResult.cpp
../src/cppunit/TextTestRunner.cpp
../src/cppunit/TypeInfoHelper.cpp
#../src/cppunit/UnixDynamicLibraryManager.cpp
#../src/cppunit/Win32DynamicLibraryManager.cpp
../src/cppunit/XmlDocument.cpp
../src/cppunit/XmlElement.cpp
../src/cppunit/XmlOutputter.cpp
../src/cppunit/XmlOutputterHook.cpp
)

if(MSVC)
   set(SOURCES ${SOURCES} ../src/cppunit/Win32DynamicLibraryManager.cpp ../src/cppunit/DllMain.cpp)
else()
   set(SOURCES ${SOURCES} ../src/cppunit/UnixDynamicLibraryManager.cpp)
endif()

set(HEADERS 
AdditionalMessage.h
Asserter.h
BriefTestProgressListener.h
CompilerOutputter.h
Exception.h
Message.h
Outputter.h
Portability.h
Protector.h
SourceLine.h
SynchronizedObject.h
Test.h
TestAssert.h
TestCaller.h
TestCase.h
TestComposite.h
TestFailure.h
TestFixture.h
TestLeaf.h
TestListener.h
TestPath.h
TestResult.h
TestResultCollector.h
TestRunner.h
TestSuccessListener.h
TestSuite.h
TextOutputter.h
TextTestProgressListener.h
TextTestResult.h
TextTestRunner.h
XmlOutputter.h
XmlOutputterHook.h
config/CppUnitApi.h
config/SelectDllLoader.h
config/SourcePrefix.h
config/config-bcb5.h
config/config-evc4.h
config/config-mac.h
config/config-msvc6.h
config-auto.h
extensions/AutoRegisterSuite.h
extensions/ExceptionTestCaseDecorator.h
extensions/HelperMacros.h
extensions/Orthodox.h
extensions/RepeatedTest.h
extensions/TestCaseDecorator.h
extensions/TestDecorator.h
extensions/TestFactory.h
extensions/TestFactoryRegistry.h
extensions/TestFixtureFactory.h
extensions/TestNamer.h
extensions/TestSetUp.h
extensions/TestSuiteBuilderContext.h
extensions/TestSuiteFactory.h
extensions/TypeInfoHelper.h
extensions/XmlInputHelper.h
plugin/DynamicLibraryManager.h
plugin/DynamicLibraryManagerException.h
plugin/PlugInManager.h
plugin/PlugInParameters.h
plugin/TestPlugIn.h
plugin/TestPlugInDefaultImpl.h
portability/CppUnitDeque.h
portability/CppUnitMap.h
portability/CppUnitSet.h
portability/CppUnitStack.h
portability/CppUnitVector.h
portability/FloatingPoint.h
portability/Stream.h
tools/Algorithm.h
tools/StringTools.h
tools/XmlDocument.h
tools/XmlElement.h
ui/mfc/MfcTestRunner.h
ui/mfc/TestRunner.h
ui/qt/Config.h
ui/qt/QtTestRunner.h
ui/qt/TestRunner.h
ui/text/TestRunner.h
ui/text/TextTestRunner.h
)

include_directories(../include)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (MSVC)
    set_property(TARGET ${DEPNAME} APPEND PROPERTY
       COMPILE_DEFINITIONS "CPPUNIT_BUILD_DLL")
endif ()

#set_target_properties(${DEPNAME}_static PROPERTIES
#    COMPILE_DEFINITIONS "")

MAKE_DIRECTORY("${CMAKE_BINARY_DIR}/dependencies/include/${DEPNAME}/")

foreach(_H_FILE ${HEADERS})
    message(${_H_FILE})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../include/${DEPNAME}/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${DEPNAME}/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING" "${CMAKE_BINARY_DIR}/dependencies/${DEPNAME}-license.txt")

