cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(env-cpp)



# add dependencies
include(FetchContent)
FetchContent_Declare(
  refl-cpp
  GIT_REPOSITORY https://github.com/veselink1/refl-cpp.git
  GIT_TAG        4684ff412bda23db3c757307f4fa16b54a5c5788 # latest
)
# set(protobuf_BUILD_TESTS OFF)
FetchContent_MakeAvailable(refl-cpp)

add_library(env-cpp INTERFACE)
add_library(env-cpp::env-cpp ALIAS env-cpp)

target_include_directories(
    env-cpp
    ${env-cpp_warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

# add the executable
add_subdirectory(examples)