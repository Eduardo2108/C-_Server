cmake_minimum_required(VERSION 3.17)
project(C__Server)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(${PROJECT_NAME} main.cpp src/Util/Coms/Response.h src/ServerManager.h src/Socket/Server.cpp src/Socket/Server.h src/ServerManager.cpp)
