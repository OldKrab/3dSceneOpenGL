cmake_minimum_required(VERSION 3.12)

project(OBJLoader)


set(OBJ_INCLUDES
	Source/OBJ_Loader.h
)


add_library(OBJLoader STATIC
Source/OBJ_Loader.h
Source/OBJ_Loader.cpp
        )

target_include_directories(OBJLoader PUBLIC Source)
set_target_properties(OBJLoader PROPERTIES LINKER_LANGUAGE C)

