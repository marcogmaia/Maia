cmake_minimum_required(VERSION 3.5)

project("Maia")
set(Maia_VERSION_MAJOR 0)
set(Maia_VERSION_MINOR 0)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(Python3 3.7 COMPONENTS Interpreter Development REQUIRED)
find_package(PythonLibs 3.7 REQUIRED)

set(
    PROJECT_SRC 
    "${PROJECT_SRC}"
    "src/main.cpp" 
    "src/Player.cpp"
    "src/pythontest.cpp"
    "src/Animation.cpp"
    "src/AnimatedSprite.cpp"
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    # ${PROJECT_SOURCE_DIR}/assets
    )

add_executable(
    ${PROJECT_NAME}
    "${PROJECT_SRC}"
)

target_link_libraries(${PROJECT_NAME} sfml-graphics pthread "${PYTHON_LIBRARIES}")


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -DNDEBUG")

# set(CMAKE_BUILD_TYPE RELEASE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
    message("CMAKE_BUILD_TYPE set to ${CMAKE_BUILD_TYPE}")
endif()