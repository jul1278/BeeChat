cmake_minimum_required (VERSION 2.6)

project ("BeeChat")

include_directories( include include// )

set( hdrs
../include/BeeChatApp.h
../include/BeeChatException.h
../include/Block.h
../include/Client.h
../include/ClientChatConnection.h
../include/ClientMessage.h
../include/GUI.h
../include/IChatConnection.h
../include/Message.h
../include/MessageFactory.h
../include/Server.h
../include/ServerChatConnection.h
../include/Snake.h
../include/theFood.h
../include/theSnake.h
../include/UDPClient.h
../include/UDPConnection.h
../include/UDPServer.h
../include/User.h
../include/UserL.h
../include/Windows.h
)

set( srcs
../src/AppMain.cpp
../src/BeeChatApp.cpp
../src/Block.cpp
../src/ChatConnectionTest.cpp
../src/Client.cpp
../src/ClientChatConnection.cpp
../src/GUI.cpp
../src/IChatConnection.cpp
../src/MessageFactory.cpp
../src/Server.cpp
../src/ServerChatConnection.cpp
../src/Snake.cpp
../src/theFood.cpp
../src/theSnake.cpp
../src/UDPClient.cpp
../src/UDPConnection.cpp
../src/UDPServer.cpp
../src/UserL.cpp
../src/Windows.cpp
)

add_executable(BeeChat ${srcs} ${hdrs} )

target_link_libraries( ${PROJECT_NAME}
pthread
ncurses
)


