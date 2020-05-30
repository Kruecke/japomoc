cmake_minimum_required(VERSION 3.14)

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
#set (CMAKE_CXX_STANDARD 11) # use instead?

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
endif()

# Threads
find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()

# SFML
include(FetchContent)
FetchContent_Declare(sfml
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(sfml)
target_link_libraries(japomoc sfml-system sfml-window sfml-graphics sfml-audio)

# Copy game resources to build directory. Should be replaced when installation is configured.
file(COPY resources DESTINATION .)
