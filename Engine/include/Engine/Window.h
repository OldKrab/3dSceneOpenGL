#pragma once
#include <memory>
#include <string>
#include "Engine/OpenGL/VertexBuffer.h"
#include "Engine/OpenGL/ShaderProgram.h"
#include "OpenGL/VertexArray.h"

struct GLFWwindow;

namespace Engine {

	class Window {
	public:
		Window(int width, int height, const char* title);

		int Start();

	private:
		int Init();
		int GlfwInit();
		static int GladInit();
		int ImGuiInit() const;

		void Render();
		void OnUpdate();
		void ImGuiRender();

		int _width, _height;
		std::string  _title;
		GLFWwindow* _window;
		std::unique_ptr<ShaderProgram> _shaderProgram;
		std::unique_ptr<VertexBuffer> _pointsVbo;
		std::unique_ptr<VertexBuffer> _colorsVbo;
		std::unique_ptr<VertexArray> _vao;
		float _backgroundColor[4];

	};

}
