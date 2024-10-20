cmake_minimum_required(VERSION 3.28)
project(TetrisClone)

set(CMAKE_CXX_STANDARD 26)

# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# Our Project
set(SOURCE_FILES
        Source/main.cpp
        Source/Public/Grid.h
        Source/Private/Grid.cpp
        Source/Public/Blocks/Block.h
        Source/Public/TetrisTypes.h
        Source/Private/Blocks/Block.cpp
        Source/Public/Blocks/Blocks.h
        Source/Private/Blocks/Blocks.cpp
        Source/Public/Tetris.h
        Source/Private/Tetris.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} raylib)


# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
