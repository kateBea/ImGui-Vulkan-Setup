cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT ImGuiVulkan)

project(${PROJECT})

set(SOURCES
    ${CMAKE_HOME_DIRECTORY}/src/main.cc
    ${CMAKE_HOME_DIRECTORY}/src/application.cc
    ${CMAKE_HOME_DIRECTORY}/src/vulkan_context.cc
    ${CMAKE_HOME_DIRECTORY}/src/window.cc
    ${CMAKE_HOME_DIRECTORY}/third-party/imgui/imgui.cpp
    ${CMAKE_HOME_DIRECTORY}/third-party/imgui/imgui_demo.cpp
    ${CMAKE_HOME_DIRECTORY}/third-party/imgui/imgui_widgets.cpp
    ${CMAKE_HOME_DIRECTORY}/third-party/imgui/imgui_draw.cpp
    ${CMAKE_HOME_DIRECTORY}/third-party/imgui/imgui_tables.cpp
    ${CMAKE_HOME_DIRECTORY}/third-party/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_HOME_DIRECTORY}/third-party/imgui/backends/imgui_impl_vulkan.cpp)

set(LIBRARIES
    volk
    glfw)
    

# Libraries ====================================================================
add_subdirectory(${CMAKE_HOME_DIRECTORY}/third-party/volk)
add_subdirectory(${CMAKE_HOME_DIRECTORY}/third-party/glfw)

# Include directories ==========================================================
include_directories(${CMAKE_HOME_DIRECTORY}/include)
include_directories(${CMAKE_HOME_DIRECTORY}/third-party/volk)
include_directories(${CMAKE_HOME_DIRECTORY}/third-party/imgui)

# Build =======================================================================
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} PRIVATE ${LIBRARIES})

# Definitions ==================================================================
# Avoid GLFW including OpenGL headers
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)