cmake_minimum_required(VERSION 3.18)

set(PROJECT ImGuiVulkan)

project(${PROJECT})

set(SOURCES
    src/main.cc
    src/application.cc
)

include_directories(${CMAKE_HOME_DIRECTORY}/include)

add_executable(${PROJECT} ${SOURCES})