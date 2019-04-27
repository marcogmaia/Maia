add_library(main STATIC AnimatedSprite.cpp Animation.cpp Player.cpp)
target_link_libraries(main fmt thor)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -O0 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -DNDEBUG")

set(CMAKE_BUILD_TYPE RELEASE)
