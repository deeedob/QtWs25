cmake_minimum_required(VERSION 3.15)

project(event_proto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Protobuf ProtobufQuick)
qt_standard_project_setup(REQUIRES 6.9)

qt_add_executable(event_qml main.cpp)
qt_add_qml_module(event_qml
    URI Event
    QML_FILES Main.qml
    SOURCES serializer.h
)

add_library(event_qml_proto STATIC)
qt_add_protobuf(event_qml_proto
    QML QML_URI Event.Proto
    PROTO_FILES event.proto
)

target_link_libraries(event_qml PRIVATE
    Qt6::Protobuf Qt6::ProtobufQuick
    event_qml_proto
)
