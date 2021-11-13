cmake_minimum_required(VERSION 3.12)

project(ImGui)

set (IMGUI_PATH imgui)

set(IMGUI_INCLUDES
	${IMGUI_PATH}/imgui.h
	${IMGUI_PATH}/backends/imgui_impl_glfw.h
	${IMGUI_PATH}/backends/imgui_impl_opengl3.h
)



set(IMGUI_SOURCES
	${IMGUI_PATH}/imgui.cpp
	${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
	${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
	${IMGUI_PATH}/imgui_demo.cpp
	${IMGUI_PATH}/imgui_tables.cpp
	${IMGUI_PATH}/imgui_widgets.cpp
	${IMGUI_PATH}/imgui_draw.cpp
)


add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
        )

target_include_directories(ImGui PUBLIC .)
target_include_directories(ImGui PUBLIC ${IMGUI_PATH})

target_link_libraries(ImGui PRIVATE glad glfw)