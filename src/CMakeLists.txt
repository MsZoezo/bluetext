cmake_minimum_required(VERSION 3.23)
project(bluetext)

set(CMAKE_CXX_STANDARD 17)

add_executable(bluetext main.cpp messages/message.cpp messages/message.h messages/userMessage.cpp messages/userMessage.h messages/systemMessage.cpp messages/systemMessage.h messages/messageCollection.cpp messages/messageCollection.h)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(bluetext Bthprops.lib wsock32 ws2_32 fmt::fmt)
