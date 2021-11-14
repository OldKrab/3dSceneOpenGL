cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME Engine)
project(${ENGINE_PROJECT_NAME})

set(INCLUDES
        include/Engine/Window.h
        )

set(SOURCES
        src/Engine/Window.cpp
        src/Engine/shaders.h)
		

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${INCLUDES}
    ${SOURCES}

)



add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(../external/imgui ${CMAKE_CURRENT_BINARY_DIR}/imgui)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)   