cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME App)

add_executable(${ENGINE_PROJECT_NAME}
     src/main.cpp
)

target_link_libraries(${ENGINE_PROJECT_NAME} Engine)


set(COPIED "TRUE" CACHE BOOL "Resoure copied")
if(${COPIED})
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/App)
endif()
set(COPIED "TRUE" CACHE BOOL "Resoure copied" FORCE)
