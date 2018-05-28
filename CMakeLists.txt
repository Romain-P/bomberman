cmake_minimum_required(VERSION 3.10)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(lib/irrlicht-1.8.4/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Linux)
add_executable(bomberman main.cpp sources/game/BomberWave.cpp include/BomberWave.hpp sources/frontend/MainMenu.cpp include/MainMenu.hpp sources/game/GameObject.cpp include/GameObject.hpp sources/game/GameManager.cpp include/GameManager.hpp sources/game/GameInputManager.cpp include/GameInputManager.hpp sources/game/GameRenderer.cpp include/GameRenderer.hpp)
target_link_libraries(bomberman Irrlicht)