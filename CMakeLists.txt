cmake_minimum_required(VERSION 2.8)
#工程名
project(MyCode C CXX)
#开启编译命令行调试
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_COMPILER "g++")
#设置全局编译参数
set(CMAKE_CXX_FLAGS "-D_FILE_OFFSET_BITS=64 -Wall -g -lpthread -std=c++0x")
#set(CMAKE_CXX_FLAGS "-D_FILE_OFFSET_BITS=64 -w -g -lpthread -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

message(STATUS "CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS})

#添加工程子目录
add_subdirectory(raft)
add_subdirectory(common)
add_subdirectory(example/timer)
add_subdirectory(example/node_status)

#复制当前编译用的common库到本地
#install(DIRECTORY /usr/local/mioji/lib/ DESTINATION lib)
