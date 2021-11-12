cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME App)

add_executable(${ENGINE_PROJECT_NAME}
     src/main.cpp
)

target_link_libraries(${ENGINE_PROJECT_NAME} Engine)

set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)