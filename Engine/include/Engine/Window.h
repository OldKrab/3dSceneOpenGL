#pragma once
#include <memory>
#include <string>
#include "Engine/OpenGL/ShaderProgram.h"

struct GLFWwindow;

namespace Engine {

	class Window {
	public:
		Window(int width, int height, const char* title);

		int Start();

	private:
		int Init();
		int GlfwInit();
		int GladInit();
		int ImGuiInit();

		void Render();
		void OnUpdate();
		void ImGuiRender();

		int _width, _height;
		std::string  _title;
		GLFWwindow* _window;
		std::unique_ptr<ShaderProgram> _shaderProgram;
		float _backgroundColor[4];

	};

}
