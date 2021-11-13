#include "Engine/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Engine
{
	Window::Window(int width, int height, const char* title)
        :_width(width), _height(height), _title(title)
	{
        Init();
	}

	int Window::Start()
	{
        glClearColor(1, 0, 0, 1);
		/* Loop until the user closes the _window */
		while (!glfwWindowShouldClose(_window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(_window);

			/* Poll for and process events */
			glfwPollEvents();
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
        if(!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))){
            glfwTerminate();
            return -1;
        }
        return 0;
    }
}
