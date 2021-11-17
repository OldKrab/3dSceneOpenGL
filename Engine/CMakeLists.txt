cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME Engine)
project(${ENGINE_PROJECT_NAME})



set(INCLUDES
        include/Engine/Window.h
		include/Engine/Shader/shaders.h
		include/Engine/Shader/ShaderProgram.h
		include/Engine/Shader/VertexBuffer.h
		include/Engine/Shader/VertexArray.h
		include/Engine/Shader/BufferLayout.h
		include/Engine/Shader/BufferElement.h
		include/Engine/Shader/IndexBuffer.h
		include/Engine/Shader/BufferUsage.h
		include/Engine/Texture.h
		include/Engine/Objects/Mesh.h
		include/Engine/Objects/Scene.h
        include/Engine/Objects/Transform.h
        include/Engine/Objects/Camera.h)

set(SOURCES
        src/Engine/Window.cpp
		src/Engine/Shader/ShaderProgram.cpp
		src/Engine/Shader/VertexBuffer.cpp
		src/Engine/Shader/VertexArray.cpp
		src/Engine/Shader/BufferLayout.cpp
		src/Engine/Shader/BufferElement.cpp
		src/Engine/Shader/IndexBuffer.cpp
		src/Engine/Shader/BufferUsage.cpp	
		src/Engine/Texture.cpp
		src/Engine/Objects/Mesh.cpp
		src/Engine/Objects/Scene.cpp
        src/Engine/Objects/Transform.cpp
		src/Engine/Objects/Camera.cpp)
		
		
set(ALL_SOURCES ${INCLUDES} ${SOURCES})

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${ALL_SOURCES}

)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_SOURCES})



add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(../external/imgui ${CMAKE_CURRENT_BINARY_DIR}/imgui)
add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
add_subdirectory(../external/stb ${CMAKE_CURRENT_BINARY_DIR}/stb)

target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC ImGui)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC stb)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)   