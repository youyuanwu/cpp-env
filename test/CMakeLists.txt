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

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(env-cpp-test example.cpp)
target_link_libraries(env-cpp-test gtest_main)
add_test(NAME all_tests COMMAND env-cpp-test)