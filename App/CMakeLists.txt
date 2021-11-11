cmake_minimum_required(VERSION 3.22)

set(ENGINE_PROJECT_NAME App)

add_executable(${ENGINE_PROJECT_NAME}
     src/main.cpp
)

target_link_libraries(${ENGINE_PROJECT_NAME} Engine)