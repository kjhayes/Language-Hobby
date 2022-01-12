message(${CMAKE_TOOLCHAIN_FILE})
message(${VCPKG_TARGET_TRIPLET})

cmake_minimum_required(VERSION 3.14)

project(Learning)

add_subdirectory(${CMAKE_SOURCE_DIR}/source)

configure_file(
  "main.lrn"
  "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 20)