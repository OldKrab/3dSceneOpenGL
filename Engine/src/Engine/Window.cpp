#include "Engine/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace Engine
{
	Window::Window(int width, int height, const char* title)
		:_width(width), _height(height), _title(title), _window(nullptr), _backgroundColor{0,0,0,1}
	{
		Init();
		ImGuiInit();
	}

	int Window::Start()
	{
		/* Loop until the user closes the _window */
		while (!glfwWindowShouldClose(_window))
		{
			OnUpdate();
			Render();
		}

		glfwTerminate();
		return 0;
	}

	int Window::Init() {
		/* Initialize the library */
		if (!glfwInit())
			return -1;

		/* Create a windowed mode _window and its OpenGL context */
		_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
		if (!_window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the _window's context current */
		glfwMakeContextCurrent(_window);

		// Init glad
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			glfwTerminate();
			return -1;
		}


		return 0;
	}

	int Window::ImGuiInit()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init();
		return 0;
	}

	void Window::Render() 
	{
		glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2], _backgroundColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGuiRender();

		glfwSwapBuffers(_window);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	void Window::ImGuiRender() 
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Background Color");
		ImGui::ColorPicker4("Pick", _backgroundColor);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
