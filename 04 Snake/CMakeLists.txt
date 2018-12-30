
cmake_minimum_required(VERSION 3.8)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

find_package(SFML COMPONENTS graphics window system)
include_directories(${SFML_INCLUDE_DIR})

add_executable(snake main.cpp)
target_link_libraries(snake ${SFML_LIBRARIES})
