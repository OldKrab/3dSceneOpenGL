#include "Engine/Window.h"
#include "shaders.h"

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

    GLuint shaderProgram;
    GLuint vao;

	Window::Window(int width, int height, const char* title)
		:_width(width), _height(height), _title(title), _window(nullptr), _backgroundColor{ 0,0,0,1 }
	{
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

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);


	}

	///////////////////////////////////////////
	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	///////////////////////////////////////////
	int Window::Init() {
		if (!glfwInit())
			return -1;

		_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
		if (!_window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(_window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			glfwTerminate();
			return -1;
		}

        glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height){
            glViewport(0,0,width,height);
        });

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexShader, nullptr);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentShader, nullptr);
        glCompileShader(fs);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vs);
        glAttachShader(shaderProgram, fs);
        glLinkProgram(shaderProgram);

        glDeleteShader(vs);
        glDeleteShader(fs);

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


		return 0;
	}

	///////////////////////////////////////////
	int Window::ImGuiInit()
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
        ImGui::DragFloat3("Points 1", points+0, 0.01);
        ImGui::DragFloat3("Points 2", points+3, 0.01);
        ImGui::DragFloat3("Points 3", points+6, 0.01);
        ImGui::ColorEdit3("Color 1", colors+0);
        ImGui::ColorEdit3("Color 2", colors+3);
        ImGui::ColorEdit3("Color 3", colors+6);

        ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
