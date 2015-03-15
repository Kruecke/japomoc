cmake_minimum_required(VERSION 2.8)

# Project name
project(japomoc)

# Add sources
add_executable(${PROJECT_NAME} src/AnimatedCharacter.cpp
                               src/AnimatedSprite.cpp
                               src/Animation.cpp
                               src/ComponentMenu.cpp
                               src/ComponentWorld.cpp
                               src/GameComponent.cpp
                               src/GameManager.cpp
                               src/main.cpp
                               src/TileMap.cpp
                               src/tinyxml2.cpp)

# Enable C++11 (and all warnings) for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
endif()

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
endif()

# Threads
find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()

# SFML
# This find module is propably not yet shipped with your cmake installation, so use a local copy.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED) # network
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# Copy game resources to build directory. Should be replaced when installation is configured.
file(COPY resources DESTINATION .)
