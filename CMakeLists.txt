cmake_minimum_required(VERSION 3.19)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpaceInvaders src/Main.cpp src/Headers/Player.hpp src/Player.cpp src/Game.cpp src/Headers/Game.hpp src/Headers/Global.hpp src/Bullet.cpp src/Headers/Bullet.hpp src/Enemy.cpp src/Headers/Enemy.hpp src/EnemyManager.cpp src/Headers/EnemyManager.hpp src/DrawText.cpp src/Headers/DrawText.hpp)

include_directories(C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories($SMFL_INCLUDE_DIR)
    target_link_libraries(SpaceInvaders ${SFML_LIBRARIES})
endif ()