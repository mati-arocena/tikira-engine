cmake_minimum_required(VERSION 3.20)
project(TiKiRa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TIDY "Run clang-tidy" OFF)
option(USE_ASAN "Build with AddressSanitizer" OFF)
option(USE_MSAN "Build with MemorySanitizer" OFF)

if(EMSCRIPTEN)
    set(BUILD_SUBDIRECTORY "web")
else()
    set(BUILD_SUBDIRECTORY "desktop")
    add_subdirectory(external)
endif()

set(PROJECT_BUILD_DIR ${CMAKE_BINARY_DIR}/${BUILD_SUBDIRECTORY})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR}/bin)

if(TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Werror -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4 /WX)
endif()

if(USE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
    link_libraries(-fsanitize=address)
elseif(USE_MSAN)
    add_compile_options(-fsanitize=memory -fno-omit-frame-pointer -g)
    link_libraries(-fsanitize=memory)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(TK_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(TK_RELEASE)
endif()

file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        SUFFIX ".html"
        COMPILE_OPTIONS "-s USE_SDL=2 -s FULL_ES2=1 -s WASM=1"
        LINK_FLAGS "-s USE_SDL=2 -s FULL_ES2=1 -s WASM=1"
    )
else()
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main GLESv2)
endif()
