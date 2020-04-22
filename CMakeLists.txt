cmake_minimum_required(VERSION 3.12)
project(serializability-checker)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

FILE(GLOB_RECURSE
        SOURCE_FILES
        src/*.cc src/*.h
        tests/*.cc tests/*.h
        )
INCLUDE("cmake/clang_checks.cmake")
