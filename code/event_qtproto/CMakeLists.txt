cmake_minimum_required(VERSION 3.15)

project(event_qtproto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Protobuf)
qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(event_qtproto main.cpp)

qt_add_protobuf(event_qtproto
    PROTO_FILES
        event.proto
)

target_link_libraries(event_qtproto PRIVATE Qt6::Protobuf)
