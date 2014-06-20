set(DEPNAME gne)


set(SOURCES
../src/Address.cpp
../src/Buffer.cpp
../src/ChannelPacket.cpp
../src/ChannelProvider.cpp
../src/ClientConnection.cpp
../src/ConditionVariable.cpp
../src/Connection.cpp
../src/ConnectionEventGenerator.cpp
../src/ConnectionListener.cpp
../src/ConnectionParams.cpp
../src/Console.cpp
../src/ConsoleBuffer.cpp
../src/ConsoleStream.cpp
../src/ConsoleStreambuf.cpp
../src/Counter.cpp
../src/CustomPacket.cpp
../src/Error.cpp
../src/Errors.cpp
../src/EventThread.cpp
../src/ExitPacket.cpp
../src/GNE.cpp
../src/GNEDebug.cpp
../src/ListServerConnection.cpp
../src/Mutex.cpp
../src/NetworkObject.cpp
../src/ObjectBroker.cpp
../src/ObjectBrokerClient.cpp
../src/ObjectBrokerPacket.cpp
../src/ObjectBrokerServer.cpp
../src/ObjectCreationPacket.cpp
../src/ObjectDeathPacket.cpp
../src/ObjectUpdatePacket.cpp
../src/Packet.cpp
../src/PacketParser.cpp
../src/PacketStream.cpp
../src/PingPacket.cpp
../src/RateAdjustPacket.cpp
../src/ReceiveEventListener.cpp
../src/ServerConnection.cpp
../src/ServerConnectionListener.cpp
../src/SocketPair.cpp
../src/SyncConnection.cpp
../src/TextConsole.cpp
../src/Thread.cpp
../src/Time.cpp
../src/Timer.cpp
../src/TimerCallback.cpp
../src/WrapperPacket.cpp
../src/gneintern.cpp
../src/conioport.c
)

#if(MSVC)
#   set(SOURCESWIN ../src/ipx.c")
#   set(SOURCES ${SOURCESWIN})
#endif()

set(HEADERS 
gnelib.h
gnelib/Address.h
gnelib/Buffer.h
gnelib/ChannelPacket.h
gnelib/ChannelProvider.h
gnelib/ClientConnection.h
gnelib/ConditionVariable.h
gnelib/Connection.h
gnelib/ConnectionEventGenerator.h
gnelib/ConnectionListener.h
gnelib/ConnectionParams.h
gnelib/ConnectionStats.h
gnelib/Console.h
gnelib/ConsoleBuffer.h
gnelib/ConsoleStream.h
gnelib/ConsoleStreambuf.h
gnelib/Counter.h
gnelib/CustomPacket.h
gnelib/Error.h
gnelib/Errors.h
gnelib/EventThread.h
gnelib/ExitPacket.h
gnelib/GNE.h
gnelib/GNEDebug.h
gnelib/ListServerConnection.h
gnelib/Lock.h
gnelib/Mutex.h
gnelib/MutexData.h
gnelib/NetworkObject.h
gnelib/ObjectBroker.h
gnelib/ObjectBrokerClient.h
gnelib/ObjectBrokerPacket.h
gnelib/ObjectBrokerServer.h
gnelib/ObjectCreationPacket.h
gnelib/ObjectDeathPacket.h
gnelib/ObjectUpdatePacket.h
gnelib/OldConsoleStreambuf.h
gnelib/Packet.h
gnelib/PacketFeeder.h
gnelib/PacketParser.h
gnelib/PacketStream.h
gnelib/PingPacket.h
gnelib/RateAdjustPacket.h
gnelib/ReceiveEventListener.h
gnelib/ServerConnection.h
gnelib/ServerConnectionListener.h
gnelib/SmartPointers.h
gnelib/SmartPtr.h
gnelib/SocketPair.h
gnelib/SyncConnection.h
gnelib/SynchronizedObject.h
gnelib/TextConsole.h
gnelib/Thread.h
gnelib/Time.h
gnelib/Timer.h
gnelib/TimerCallback.h
gnelib/WeakPtr.h
gnelib/WrapperPacket.h
gnelib/conioport.h
gnelib/gneintern.h
gnelib/gnetypes.h
)

FIND_PACKAGE(Boost REQUIRED)

include_directories(../include ../../../dependencies/include ${Boost_INCLUDE_DIR})

cegui_add_library(${DEPNAME} SOURCES NONE)

target_link_libraries(${DEPNAME} NL)

if (APPLE)
 
    target_link_libraries(${DEPNAME} curses)

    set_property(TARGET ${DEPNAME} APPEND PROPERTY
       COMPILE_DEFINITIONS "_REENTRANT;MACOSX")
    set_target_properties(${DEPNAME}_static PROPERTIES
       COMPILE_DEFINITIONS "_REENTRANT;MACOSX")

endif ()

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../include/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../License" "${CMAKE_BINARY_DIR}/dependencies/${DEPNAME}-license.txt")

