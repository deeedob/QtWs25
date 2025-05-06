cmake_minimum_required(VERSION 3.15)

project(event_proto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)

add_executable(event_proto main.cpp)

set(proto_dir "${CMAKE_CURRENT_LIST_DIR}")
set(proto_out "${CMAKE_CURRENT_BINARY_DIR}")

protobuf_generate(
    TARGET event_proto
    PROTOS "${proto_dir}/event.proto"
    IMPORT_DIRS "${proto_dir}"
    PROTOC_OUT_DIR "${proto_out}"
    OUT_VAR proto_gens
)

set_source_files_properties(${proto_gens} PROPERTIES
    GENERATED ON
    SKIP_UNITY_BUILD_INCLUSION ON
)

target_link_libraries(event_proto PRIVATE protobuf::libprotobuf)
target_include_directories(event_proto PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
