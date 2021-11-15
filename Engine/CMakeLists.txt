cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME Engine)
project(${ENGINE_PROJECT_NAME})

set(INCLUDES
        include/Engine/Window.h
		include/Engine/OpenGL/shaders.h
		include/Engine/OpenGL/ShaderProgram.h
		include/Engine/OpenGL/VertexBuffer.h
		include/Engine/OpenGL/VertexArray.h
        )

set(SOURCES
        src/Engine/Window.cpp
		src/Engine/OpenGL/ShaderProgram.cpp
		src/Engine/OpenGL/VertexBuffer.cpp
		src/Engine/OpenGL/VertexArray.cpp
		)
		
		
set(ALL_SOURCES ${INCLUDES} ${SOURCES})

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${ALL_SOURCES}

)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_SOURCES})



add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(../external/imgui ${CMAKE_CURRENT_BINARY_DIR}/imgui)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)   