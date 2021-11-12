#include <cstddef>
#include "Engine/Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Engine
{
	Application::Application()
	{
	}

	int Application::start(unsigned int height, unsigned int width, const char* title)
	{
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
			return -1;

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

        // Init glad
        if(!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))){
            glfwTerminate();
            return -1;
        }

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();
		return 0;
	}
}
