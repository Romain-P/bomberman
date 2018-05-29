cmake_minimum_required(VERSION 3.10)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(lib/irrlicht-1.8.4/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Linux)
add_executable(bomberman main.cpp sources/network/NetworkAsyncListener.cpp include/NetworkAsyncListener.h sources/network/NetworkSocket.cpp include/NetworkSocket.h include/Network.h)
target_link_libraries(bomberman Irrlicht)