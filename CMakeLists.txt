cmake_minimum_required(VERSION 3.20)
project(TiKiRa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TIDY "Run clang-tidy" ON)
option(USE_ASAN "Build with AddressSanitizer" OFF)
option(USE_MSAN "Build with MemorySanitizer" OFF)

if(TIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set_property(SOURCE ${SOURCES} PROPERTY COMPILE_OPTIONS -Wall -Werror -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(TiKiRa PRIVATE /W4 /WX)
endif()

if(USE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
elseif(USE_MSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory -fno-omit-frame-pointer -g")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=memory")
endif()

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(USE_FLAGS "-s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
else()
    add_subdirectory(external/SDL)
endif()

file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(EMSCRIPTEN)
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${ADDITIONAL_EMSDK_PATHS}
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        COMPILE_FLAGS "-I${CMAKE_CURRENT_SOURCE_DIR}/include"
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-s USE_SDL=2 -s FULL_ES2=1 -s WASM=1"
    )
else()
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${SDL_INCLUDE_DIRS}
    )
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main GLESv2)
endif()
