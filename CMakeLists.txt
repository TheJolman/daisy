cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(daisyc CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES src/main.cpp src/test.cpp src/scanner.cpp)

# LLVM
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader)

# CLI11
find_package(CLI11 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING "Choose the type of build (Debug, Release)" FORCE)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE $<$<CONFIG:Debug>:-g
          -O0
          -Wall
          -Wextra
          -U_FORTIFY_SOURCE>
          $<$<CONFIG:Release>:-O3
          -DNDEBUG
          -D_FORTIFY_SOURCE=2>)
target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs})
target_link_libraries(${PROJECT_NAME} PRIVATE CLI11::CLI11)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# GTest
find_package(GTest REQUIRED)
enable_testing()
add_executable(tests tests/tests.cpp)
target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)

# format target
add_custom_target(
  format
  COMMAND clang-format -i ${CMAKE_SOURCE_DIR}/src/*.cpp
          ${CMAKE_SOURCE_DIR}/include/*.hpp
  COMMENT "Format code with clang-format")

# static analysis target
add_custom_target(
  tidy
  COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR}
  COMMENT "Check code with clang-tidy")
