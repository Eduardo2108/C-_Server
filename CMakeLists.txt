cmake_minimum_required(VERSION 3.17)
project(C__Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(C__Server main.cpp src/Types/Integer.h src/Types/Double.h src/Types/Char.h src/Types/Float.h src/Types/Long.h src/Types/Reference.h src/Types/Struct.h src/Types/GenericType.h src/Util/Json.h src/Coms/Message.h src/Constants.h src/Util/Converter.h src/DataStructures/LinkedList.h src/DataStructures/Queue.h src/DataStructures/BinarySearchTree.h src/MemoryManagement/Collector.h src/ServerManager.h src/Coms/Comunicator.h src/Coms/Response.h)