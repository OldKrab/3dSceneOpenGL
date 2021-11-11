cmake_minimum_required(VERSION 3.22)

set(ENGINE_PROJECT_NAME Engine)

add_library(${ENGINE_PROJECT_NAME} STATIC
    src/Engine/temp.cpp
    include/Engine/temp.h
)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)   