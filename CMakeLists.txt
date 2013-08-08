# minimum version of CMake needed (used version).
cmake_minimum_required(VERSION 2.6)

# Our project name: Moteur2D
project(Moteur2D)

set(MOTEUR2D_SOURCE_DIR ".")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Building in '${CMAKE_BUILD_TYPE}' mode")

# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++0x -W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused-parameter")

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

# Custom cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Moteur2D include directory
include_directories("include")

# Moteur2D sources
file(GLOB_RECURSE MOTEUR2D_SOURCES ${MOTEUR2D_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MOTEUR2D_SOURCES ${MOTEUR2D_SOURCE_DIR}/src/main.cpp)
set(MOTEUR2D_LIB "MOTEUR2D_lib")
add_library(${MOTEUR2D_LIB} ${MOTEUR2D_SOURCES})

# OpenGL
# include(FindOpenGL)
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${MOTEUR2D_LIB} ${OPENGL_LIBRARIES})

# lib PNG
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(${MOTEUR2D_LIB} ${PNG_LIBRARY})

# GLUT
find_package(GLUT)
include_directories(${GLUT_INCLUDE_DIR})
target_link_libraries(${MOTEUR2D_LIB} ${GLUT_LIBRARIES})

# SOIL
find_package(SOIL)
include_directories(${SOIL_INCLUDE_DIR})
target_link_libraries(${MOTEUR2D_LIB} ${SOIL_LIBRARIES})

# GLM
find_package(GLM)
include_directories(${GLM_INCLUDE_DIR})
target_link_libraries(${MOTEUR2D_LIB} ${GLM_LIBRARIES})

# CTags target
set(CTAGS_TARGET_NAME "tags")
set(CTAGS_SCRIPT "ctags.sh")
set(CTAGS_CMD ${CMAKE_CURRENT_SOURCE_DIR}/${CTAGS_SCRIPT})
add_custom_target(
    ${CTAGS_TARGET_NAME}
    COMMAND ${CTAGS_CMD})

# Tests
add_subdirectory("tests")
