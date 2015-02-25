cmake_minimum_required(VERSION 2.8)

project(japomoc)

# Just for developement purposes: Use Clang if available
#if(EXISTS "/usr/bin/clang++")
#    set(CMAKE_CXX_COMPILER "clang++")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#endif()

# Enable C++11 for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Add sources
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
endif()

# SFML
# This module is propably not yet shipped with you cmake installation, so use a local copy.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED) # network
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# Copy some resources
file(COPY resources DESTINATION .)
