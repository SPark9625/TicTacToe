cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(TicTacToe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -pedantic")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LINUX")
endif()

set(CMAKE_PREFIX_PATH /usr/local/libtorch)
find_package(Torch REQUIRED)

add_library(tictactoe tictactoe.cpp)

target_link_libraries(tictactoe "${TORCH_LIBRARIES}")
set_property(TARGET tictactoe PROPERTY CXX_STANDARD 17)