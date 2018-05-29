cmake_minimum_required(VERSION 3.10)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(lib/irrlicht-1.8.4/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Linux)
add_executable(bomberman main.cpp sources/shared/ANetworkAsyncListener.cpp include/shared/ANetworkAsyncListener.h sources/shared/NetworkSocket.cpp include/shared/NetworkSocket.h include/shared/Network.h sources/shared/ANetworkAsyncServer.cpp include/shared/ANetworkAsyncServer.h include/shared/INetworkClientHandler.h sources/shared/NetworkClient.cpp include/shared/NetworkClient.h include/shared/ANetworkClientAdapter.h sources/shared/ANetworkBuffer.cpp include/shared/ANetworkBuffer.h)
target_link_libraries(bomberman Irrlicht)