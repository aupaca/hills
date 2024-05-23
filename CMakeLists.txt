cmake_minimum_required(VERSION 3.14.5)
project(runToTheHills)
add_subdirectory(./engine/andronaut)
include_directories("${CMAKE_SOURCE_DIR}/src/"
                    "${CMAKE_SOURCE_DIR}/engine/"
                    "${CMAKE_SOURCE_DIR}/libs/glm/")

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_library(hills SHARED ${SRC_FILES})
target_link_libraries(hills PRIVATE andronaut)