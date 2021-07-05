# import google test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(env-cpp-tests CXX)

set(
    tests
    parse
    example
)

foreach(test IN LISTS tests)
  add_executable("${test}-test" "${test}-test.cpp")
  target_link_libraries("${test}-test" PRIVATE gtest_main env-cpp::env-cpp refl-cpp)
  target_compile_features("${test}-test" PRIVATE cxx_std_17)
  add_test(NAME "${test}-test" COMMAND "${test}-test")
endforeach()