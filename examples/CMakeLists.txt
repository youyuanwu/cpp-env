cmake_minimum_required(VERSION 3.14)

project(refl-cpp-examples CXX)

set(
    examples
    main
)

foreach(example IN LISTS examples)
  add_executable("${example}" "example-${example}.cpp")
  target_link_libraries("${example}" PRIVATE env-cpp::env-cpp refl-cpp)
  target_compile_features("${example}" PRIVATE cxx_std_17)
endforeach()