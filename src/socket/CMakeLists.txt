set(SOCKET_SOURCES

    # Socket
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_tcp/TCPServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_tcp/SimpleTCPServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_tcp/TCPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_tcp/SimpleTCPClient.cpp
)

set(SOCKET_SOURCES ${SOCKET_SOURCES} PARENT_SCOPE)