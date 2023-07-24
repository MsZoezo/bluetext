cmake_minimum_required(VERSION 3.25)
project(BlueText)

set(CMAKE_CXX_STANDARD 20)

add_executable(BlueText src/main.cpp src/console.cpp src/console.h src/message.cpp src/message.h src/inputBuffer.cpp src/inputBuffer.h src/clients/client.cpp src/clients/client.h src/messageCollection.cpp src/messageCollection.h src/messageCollection.h src/clients/hostClient.cpp src/clients/hostClient.h src/clients/remote.cpp src/clients/remote.h src/clients/guestClient.cpp src/clients/guestClient.h)

target_link_libraries(BlueText Bthprops.lib wsock32 ws2_32)