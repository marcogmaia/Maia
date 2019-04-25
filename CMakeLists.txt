cmake_minimum_required(VERSION 3.5)

project("Maia")

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14 -Wall")