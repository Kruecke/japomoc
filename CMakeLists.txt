cmake_minimum_required(VERSION 3.11)

# Program name
project(japomoc)

# Use modern C++
set (CMAKE_CXX_STANDARD 11)

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

# TODO: There should be a cleaner solution for this!?
#       (I think this is only needed when not using default CMake)
list(APPEND CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)

# SFML
find_package(SFML 2 COMPONENTS system window graphics audio)
if(SFML_FOUND)
    # TODO: Why no need for SFML include here?
    #include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
else()
    message(STATUS "SFML not found. Fetching from Github...")
    include(FetchContent)
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
    )
    if(${CMAKE_VERSION} VERSION_LESS 3.14)
        # CMake 3.11+
        FetchContent_GetProperties(sfml)
        if(NOT sfml_POPULATED)
            FetchContent_Populate(sfml)
            add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
        endif()
    else()
        # CMake 3.14+
        FetchContent_MakeAvailable(sfml)
    endif()
    # TODO: Why is this different from when SFML has been found?
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
endif()

# Threads, also used by SFML
find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()

# Copy game resources to build directory. Should be replaced when installation is configured.
file(COPY resources DESTINATION .)

