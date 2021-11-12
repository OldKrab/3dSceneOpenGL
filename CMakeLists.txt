cmake_minimum_required(VERSION 3.12)

project(3dSceneOpenGL)

add_subdirectory(Engine)
add_subdirectory(App)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)
