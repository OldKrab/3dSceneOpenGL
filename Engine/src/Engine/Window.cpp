#include "Engine/Window.h"
#include "Engine/Shader/shaders.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{
	static GLfloat points_colors_tex[]
	{
		-0.5f, -0.5f, 0.0f,		0.0f,  0.0f,  1.0f,		 0.0f,  0.0f,
		-0.5f,  0.5f, 0.0f,		1.0f,  0.0f,  0.0f,		 0.0f,  1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f,  1.0f,  0.0f,		 1.0f,  0.0f,
		 0.5f,  0.5f, 0.0f,		0.0f,  1.0f,  0.0f,		 1.0f,  1.0f,
	};

	static GLuint indexes[]{
		0, 1, 2, 2, 1, 3
	};

	Window::Window(int width, int height, const char* title)
		:_width(width), _height(height), _title(title), _window(nullptr), _backgroundColor{ 1,0,1,1 }
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
	static glm::mat4 origTrans = glm::mat4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	static glm::mat4 trans = glm::mat4(1.0f);
	static glm::vec3 _scale = glm::vec3(1.f, 1.f, 0.f);
	static glm::vec3 _translate = glm::vec3(0.f, 0.f, 0.f);
	static float _rotate = 0;
	static bool _rotating = true;

	///////////////////////////////////////////
	void Window::Render()
	{
		glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2], _backgroundColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		_texture->Bind();
		_shaderProgram->Use();
		_vao->Bind();

		_shaderProgram->SetUniformMatrix4fv("transform", trans);
		glDrawElements(GL_TRIANGLES, _vao->GetIndexesCount(), GL_UNSIGNED_INT, nullptr);
	}

	///////////////////////////////////////////
	void Window::OnUpdate()
	{
		glfwPollEvents();
		static int fps = 0;
		static double time = 0;
		static double prevTime = 0;

		double curTime = glfwGetTime();
		double deltaTime = curTime - prevTime;
		prevTime = curTime;

		fps++;
		time += deltaTime;
		if (time > 1)
		{
			time -= 1.;
			glfwSetWindowTitle(_window, (std::string("FPS:") + std::to_string(fps)).c_str());
			fps = 0;
		}

		if (_rotating)
			_rotate += 2.5f * (float)deltaTime;

		glm::mat4 scale_matrix(_scale[0], 0, 0, 0,
			0, _scale[1], 0, 0,
			0, 0, _scale[2], 0,
			0, 0, 0, 1);

		glm::mat4 rotate_matrix(cos(_rotate), sin(_rotate), 0, 0,
			-sin(_rotate), cos(_rotate), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		glm::mat4 translate_matrix(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			_translate[0], _translate[1], _translate[2], 1);

		trans = rotate_matrix * translate_matrix * scale_matrix * origTrans;
	}

	///////////////////////////////////////////
	int Window::Init() {
		_shaderProgram = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);

		BufferLayout layout({ {GL_FLOAT, 3}, {GL_FLOAT, 3}, {GL_FLOAT, 2} });
		_vbo = std::make_unique<VertexBuffer>(points_colors_tex, sizeof(points_colors_tex), layout, BufferUsage::Static);
		_ibo = std::make_unique<IndexBuffer>(indexes, sizeof(indexes), 6, BufferUsage::Static);

		_vao = std::make_unique<VertexArray>();

		_vao->AddVertexBuffer(*_vbo);
		_vao->SetIndexBuffer(*_ibo);

		_texture = std::make_unique<Texture>("assets/tex.jpg");
		_texture->SetParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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

		//ImGui::ShowDemoWindow();

		ImGui::Begin("Debug");
		ImGui::ColorEdit4("Background Color", _backgroundColor);
		ImGui::DragFloat3("Scale", &_scale[0], 0.01f);
		ImGui::DragFloat3("Translate", &_translate[0], 0.01f);
		ImGui::DragFloat("Rotate", &_rotate, 0.01f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
