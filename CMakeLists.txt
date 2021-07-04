cmake_minimum_required(VERSION 3.11)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(cpp-env)



# add dependencies
include(FetchContent)
FetchContent_Declare(
  refl-cpp
  GIT_REPOSITORY https://github.com/veselink1/refl-cpp.git
  GIT_TAG        4684ff412bda23db3c757307f4fa16b54a5c5788 # latest
)
# set(protobuf_BUILD_TESTS OFF)
FetchContent_MakeAvailable(refl-cpp)


# add the executable
add_executable(main main.cpp)
target_link_libraries(main  refl-cpp)

add_executable(example example.cpp)
target_link_libraries(example  refl-cpp)