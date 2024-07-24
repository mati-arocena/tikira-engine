cmake_minimum_required(VERSION 3.20)
project(TikiraExternalDependencies)

set(EXTERNAL_BUILD_DIR ${CMAKE_BINARY_DIR}/external)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXTERNAL_BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXTERNAL_BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXTERNAL_BUILD_DIR}/bin)

add_subdirectory(SDL)
#add_subdirectory(tracy)

if(BUILD_TESTS)
    add_subdirectory(catch2)
endif()
