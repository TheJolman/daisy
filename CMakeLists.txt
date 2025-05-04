cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(daisy CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES src/main.cpp)

set(HEADERS include/test.hpp)

find_package(libllvm 19.1 QUIET)

set(LLVM_LIBRARY libllvm)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LLVM_LIBRARY})
