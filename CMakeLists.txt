cmake_minimum_required(VERSION 3.17)
project(C__Server)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

if (SPDLOG_BUILD_EXAMPLE_HO)
    target_link_libraries(example_header_only PRIVATE spdlog::spdlog_header_only)
endif ()


add_executable(${PROJECT_NAME} main.cpp src/Util/Coms/Response.h src/ServerManager.h src/Socket/Server.cpp src/Socket/Server.h src/ServerManager.cpp)
