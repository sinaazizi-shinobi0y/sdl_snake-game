cmake_minimum_required(VERSION 3.10)


project(snake_game)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} snake_game/main.cpp
           snake_game/jj.h )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
