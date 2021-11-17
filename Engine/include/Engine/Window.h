#pragma once
#include <memory>
#include <string>
#include <Engine/Objects/Mesh.h>

#include "Texture.h"
#include "Engine/Shader/VertexBuffer.h"
#include "Engine/Shader/ShaderProgram.h"
#include "Shader/VertexArray.h"

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
		std::unique_ptr<Mesh> _cube;
		float _backgroundColor[4];

	};

}
