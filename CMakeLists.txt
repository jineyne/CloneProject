cmake_minimum_required(VERSION 3.10)

project(CloneProject)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
else ()
    add_compile_options(-m64)
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Source)
add_subdirectory(Vender)
