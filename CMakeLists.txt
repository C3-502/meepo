cmake_minimum_required(VERSION 3.5)
project(meepo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(SOURCE_FILES src/main.cpp src/net/poller.cpp src/net/poller.h src/common/macro.h src/net/io_loop.cpp src/net/io_loop.h src/net/socket.h src/net/socket.cpp src/net/net_addr.h src/net/net_addr.cpp)
add_executable(meepo ${SOURCE_FILES})