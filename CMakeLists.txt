cmake_minimum_required(VERSION 3.11)
project(TiKiRa)
set(CMAKE_CXX_STANDARD 20)

# Check if using Emscripten
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line changes the output to HTML
    set(USE_FLAGS "-s USE_SDL=2 -s FULL_ES2=1 -s WASM=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
else()
    include(FetchContent)
    FetchContent_Declare(
      SDL2
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG release-2.30.5
    )
    FetchContent_MakeAvailable(SDL2)
endif()

file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(EMSCRIPTEN)
    target_link_libraries(${PROJECT_NAME} "-s USE_SDL=2 -s FULL_ES2=1 -s WASM=1")
else()
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main GLESv2)
endif()
