cmake_minimum_required(VERSION 3.5.1)

project(prototype-db-2 VERSION 0.0.1 LANGUAGES CXX)

#
# Common properties
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

set(BUILD_SUPPORT_DIR ${CMAKE_SOURCE_DIR}/build-support)

find_package(gRPC CONFIG REQUIRED)

#
# Target: protodb2
#

add_executable(protodb2)

target_compile_definitions(protodb2
  PRIVATE
    USE_LIBCUCKOO_STORAGE_ENGINE=1
    USE_FOLLY_STORAGE_ENGINE=0 
)

target_compile_features(protodb2 PRIVATE cxx_std_17)

# Protobuf compilation

get_filename_component(protodb2_proto "${CMAKE_CURRENT_SOURCE_DIR}/src/proto/protodb2.proto" ABSOLUTE)
get_filename_component(protodb2_proto_path "${protodb2_proto}" PATH)

set(protodb2_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/protodb2.pb.cc")
set(protodb2_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/protodb2.pb.h")
set(protodb2_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/protodb2.grpc.pb.cc")
set(protodb2_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/protodb2.grpc.pb.h")
add_custom_command(
      OUTPUT "${protodb2_proto_srcs}" "${protodb2_proto_hdrs}" "${protodb2_grpc_srcs}" "${protodb2_grpc_hdrs}"
      COMMAND protoc
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        --proto_path "${protodb2_proto_path}"
        --plugin=protoc-gen-grpc="/usr/bin/grpc_cpp_plugin"
        "${protodb2_proto}"
      DEPENDS "${protodb2_proto}")

target_sources(protodb2
  PRIVATE
    "src/main.cc"
    "src/grpc_server.cc"
    "${protodb2_proto_srcs}"
    "${protodb2_grpc_srcs}"
)

target_include_directories(protodb2
  PRIVATE 
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/thirdparty"
    "${LIBUV_INCLUDE_DIRS}"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(protodb2
  PRIVATE 
    "${LIBUV_LIBRARIES}"
    "${JEMALLOC_LIBRARIES}"
    folly
    glog
    pthread
    gRPC::grpc++
    gRPC::grpc++_reflection
)

#
# Compiler Tools
#

set(CLANG_FORMAT_VERSION_PATTERN "10")
set(CLANG_TIDY_VERSION_PATTERN "10")
find_package(ClangTools)

#
# make format
#

if(${CLANG_FORMAT_FOUND})
  # runs clang format and updates files in place.
  add_custom_target(
    format
    ${BUILD_SUPPORT_DIR}/run_clang_format.py
    ${CLANG_FORMAT_BIN}
    ${BUILD_SUPPORT_DIR}/clang_format_exclusions.txt
    --source_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    --fix)

  # runs clang format and exits with a non-zero exit code if any files need to
  # be reformatted
  add_custom_target(
    check-format ${BUILD_SUPPORT_DIR}/run_clang_format.py ${CLANG_FORMAT_BIN}
    ${BUILD_SUPPORT_DIR}/clang_format_exclusions.txt --source_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()

#
# make check-clang-tidy
#
# Copied from https://github.com/cmu-db/terrier/blob/master/CMakeLists.txt
#

if (${CLANG_TIDY_FOUND})
    add_custom_target(check-clang-tidy
            ${BUILD_SUPPORT_DIR}/run-clang-tidy.py                            # run LLVM's clang-tidy script
            -clang-tidy-binary ${CLANG_TIDY_BIN}                              # using our clang-tidy binary
            -p ${CMAKE_BINARY_DIR}                                            # using cmake's generated compile commands
            )
endif ()

