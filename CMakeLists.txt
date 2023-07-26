cmake_minimum_required(VERSION 3.25)
project(BlueText)

set(CMAKE_CXX_STANDARD 20)

add_executable(BlueText src/main.cpp src/console.cpp src/console.h src/message.cpp src/message.h src/input/inputBuffer.cpp src/input/inputBuffer.h src/networkables/networkable.cpp src/networkables/networkable.h src/messageCollection.cpp src/messageCollection.h src/messageCollection.h src/networkables/bluetooth/btServer.cpp src/networkables/bluetooth/btServer.h src/networkables/remote.cpp src/networkables/remote.h src/networkables/bluetooth/btClient.cpp src/networkables/bluetooth/btClient.h src/input/inputHandler.cpp src/input/inputHandler.h)

target_link_libraries(BlueText Bthprops.lib wsock32 ws2_32 --static)