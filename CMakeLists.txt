cmake_minimum_required(VERSION 3.2)
project(OS32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(header)

set(TEAM1_SOURCE src/team1/OS32Memory.cpp src/team1/File.cpp src/team1/FileSystem.cpp)
set(TEAM2_SOURCE src/team2/chper.cpp src/team2/DCreate.cpp src/team2/FCreate.cpp src/team2/Fread.cpp src/team2/Fwrite.cpp src/team2/helpme1.cpp src/team2/ListItems.cpp)
set(TEAM3_SOURCE src/team3/Login.cpp src/team3/Menu.cpp src/team3/UI.cpp)
set(TEAM4_SOURCE src/team4/Converter.cpp src/team4/CSCI3132-UtilitiesMain.cpp src/team4/encryption.cpp src/team4/main.cpp src/team4/Motd.cpp src/team4/Palindrome.cpp src/team4/Utilities.cpp)

add_executable(OS32 ${TEAM1_SOURCE} ${TEAM2_SOURCE} ${TEAM3_SOURCE} ${TEAM4_SOURCE})
