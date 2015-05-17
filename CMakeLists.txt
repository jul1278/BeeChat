cmake_minimum_required (VERSION 2.6)

project ("BeeChat")

include_directories( include include/ConnectionLayer/ )

set( srcs
    ./src/AppMain.cpp
    ./src/BeeChatApp.cpp
    ./src/ConnectionLayer/IChatConnection.cpp
    ./src/ConnectionLayer/ServerChatConnection.cpp
    ./src/ConnectionLayer/ClientChatConnection.cpp
    ./src/ConnectionLayer/UDPServer.cpp 
	./src/ConnectionLayer/UDPClient.cpp
	./src/ConnectionLayer/UDPConnection.cpp
	./src/Client.cpp
	./src/Server.cpp
)

add_executable(BeeChat ${srcs} )
