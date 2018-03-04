cmake_minimum_required(VERSION 2.8)
project(fsuemulator)

set(CMAKE_CXX_STANDARD 11)

#配置编译选项
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb -Wall")
#配置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive -pthread")

#配置头文件目录
include_directories(
        /opt/deps-cloud/sengine/boost_1_59_0_x86/include
        /usr/local/include
)

include_directories(./easylogger/include)
include_directories(./tinyxml/include)
include_directories(./include)

#set(SOURCE_FILES
#        ./src
#        ./easylogger
#        )
aux_source_directory(./src SOURCE_FILES)
aux_source_directory(./easylogger SOURCE_FILES)
aux_source_directory(./tinyxml SOURCE_FILES)

#添加共享库文件
link_directories(
        /usr/local/lib/
        /opt/deps-cloud/sengine/boost_1_59_0_x86/lib/
)

set(LIBRARIES
        libpaho-mqtt3a.so
        libboost_serialization.so
        )

add_executable(fsuemulator ${SOURCE_FILES})

#共享库链接
TARGET_LINK_LIBRARIES(fsuemulator ${LIBRARIES})