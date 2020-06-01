cmake_minimum_required(VERSION 3.11)

# Program name
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

# Use modern C++
set (CMAKE_CXX_STANDARD 11)

# SFML
find_package(SFML 2 COMPONENTS system window graphics audio)
if(NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
    )
    if(${CMAKE_VERSION} VERSION_LESS 3.14)
        # CMake 3.11+
        FetchContent_GetProperties(SFML)
        if(NOT SFML_POPULATED)
            FetchContent_Populate(SFML)
            add_subdirectory(${SFML_SOURCE_DIR} ${SFML_BINARY_DIR})
        endif()
    else()
        # CMake 3.14+
        FetchContent_MakeAvailable(SFML)
    endif()
endif()
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)

# Threads, also used by SFML
find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()

# Copy game resources to build directory. Should be replaced when installation is configured.
file(COPY resources DESTINATION .)
