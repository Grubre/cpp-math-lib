cmake_minimum_required(VERSION 3.13)
project(cpp_math_lib)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  vector
  tests/vector_unittest.cpp
)
target_link_libraries(
  vector
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector)
