cmake_minimum_required(VERSION 3.5)

project(Maia VERSION 0.0.0)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(Python3 3.7 COMPONENTS Interpreter Development REQUIRED)
find_package(PythonLibs 3.7 REQUIRED)

add_subdirectory(src)
add_subdirectory(lib/Thor)
add_subdirectory(lib/fmt)
add_subdirectory(lib/tmxlite/tmxlite)

include_directories("${PROJECT_SOURCE_DIR}/include"
                    "${PROJECT_SOURCE_DIR}/lib/fmt/include")

add_executable(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/src/main.cpp")

target_link_libraries(${PROJECT_NAME} sfml-graphics pthread
                      # "${PYTHON_LIBRARIES}"
                      player fmt
                      # tmxlite
                      )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -O0 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -DNDEBUG")

set(CMAKE_BUILD_TYPE RELEASE)
message("CMAKE_BUILD_TYPE set to ${CMAKE_BUILD_TYPE}")
