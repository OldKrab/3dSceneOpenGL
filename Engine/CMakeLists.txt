cmake_minimum_required(VERSION 3.22)

set(ENGINE_PROJECT_NAME Engine)

add_library(${ENGINE_PROJECT_NAME} STATIC

    include/Engine/temp.h
    src/Engine/temp.cpp
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)   