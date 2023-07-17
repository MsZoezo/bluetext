cmake_minimum_required(VERSION 3.25)
project(BlueText)

set(CMAKE_CXX_STANDARD 20)

add_executable(BlueText src/main.cpp src/console.cpp src/console.h src/message.cpp src/message.h)
