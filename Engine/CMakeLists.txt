cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME Engine)

set(INCLUDES
    include/Engine/Application.h
)

set(SOURCES
    src/Engine/Application.cpp
)

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${SOURCES}
    ${INCLUDES}
)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)   