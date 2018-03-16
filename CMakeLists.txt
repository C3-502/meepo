cmake_minimum_required(VERSION 3.5)
project(meepo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(SOURCE_FILES src/main.cpp src/net/poller.cpp src/net/poller.h src/common/macro.h src/net/io_loop.cpp src/net/io_loop.h src/net/net_addr.h src/net/net_addr.cpp src/net/tcp_listener.h src/net/tcp_listener.cpp src/net/tcp_connection.h src/net/tcp_connection.cpp src/net/net_common.h src/net/io_buffer.cpp src/net/io_buffer.h)
add_executable(meepo ${SOURCE_FILES})