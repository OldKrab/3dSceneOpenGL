#include "Engine/Window.h"
#include "Engine/OpenGL/shaders.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace Engine
{
	static GLfloat points[]
	{
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	static GLfloat colors[]
	{
		 1.0f,  0.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  0.0f,  1.0f
	};


	Window::Window(int width, int height, const char* title)
		:_width(width), _height(height), _title(title), _window(nullptr), _backgroundColor{ 0,0,0,1 }
	{
		GlfwInit();
		GladInit();
		Init();
		ImGuiInit();
	}

	///////////////////////////////////////////
	int Window::Start()
	{
		while (!glfwWindowShouldClose(_window))
		{
			OnUpdate();
			Render();
			ImGuiRender();
			glfwSwapBuffers(_window);
		}

		glfwTerminate();
		return 0;
	}

	///////////////////////////////////////////
	void Window::Render()
	{
		glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2], _backgroundColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		_shaderProgram->Use();
		_vao->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	///////////////////////////////////////////
	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	///////////////////////////////////////////
	int Window::Init() {

		_shaderProgram = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);

		_pointsVbo = std::make_unique<VertexBuffer>(points, sizeof(points), VertexBuffer::Usage::Static);
		_colorsVbo = std::make_unique<VertexBuffer>(colors, sizeof(colors), VertexBuffer::Usage::Static);


		_vao = std::make_unique<VertexArray>();

		_vao->AddBuffer(*_pointsVbo);
		_vao->AddBuffer(*_colorsVbo);

		return 0;
	}

	///////////////////////////////////////////
	int Window::GlfwInit()
	{
		if (!glfwInit())
			return -1;

		_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
		if (!_window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(_window);

		glfwSetFramebufferSizeCallback(_window,
			[](GLFWwindow* window, int width, int height) {
				glViewport(0, 0, width, height);
			});
		return 0;
	}

	///////////////////////////////////////////
	int Window::GladInit()
	{
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			return -1;
		}
		return 0;
	}

	///////////////////////////////////////////
	int Window::ImGuiInit() const
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init();
		return 0;
	}

	///////////////////////////////////////////
	void Window::ImGuiRender()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Debug");
		ImGui::ColorEdit4("Background Color", _backgroundColor);
		ImGui::DragFloat3("Points 1", points + 0, 0.01f);
		ImGui::DragFloat3("Points 2", points + 3, 0.01f);
		ImGui::DragFloat3("Points 3", points + 6, 0.01f);
		ImGui::ColorEdit3("Color 1", colors + 0);
		ImGui::ColorEdit3("Color 2", colors + 3);
		ImGui::ColorEdit3("Color 3", colors + 6);

		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
