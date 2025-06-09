cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(daisyc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES src/main.cpp src/test.cpp)

# LLVM
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader)

# CLI11
find_package(CLI11 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs})
target_link_libraries(${PROJECT_NAME} PRIVATE CLI11::CLI11)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# GTest
find_package(GTest REQUIRED)
enable_testing()
add_executable(
  tests
  tests/tests.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
