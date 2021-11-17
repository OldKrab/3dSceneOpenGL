#pragma once
#include <memory>
#include <string>
#include <Engine/Objects/Mesh.h>
#include <Engine/Objects/Scene.h>
#include <Engine/Objects/Model.h>

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
        void SetScene(Scene&& scene);
	private:
		int Init();
		int GlfwInit();
		static int GladInit();
		int ImGuiInit() const;

		void Render();
		void OnUpdate();
		void ImGuiRender();

		void UpdateCameraPos(float delta);
		void SetProjection(int width, int height);
        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void MousePosCallback(GLFWwindow* window, double xpos, double ypos);
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		int _width, _height;
		std::string  _title;
		GLFWwindow* _window;
		std::unique_ptr<ShaderProgram> _shaderProgram;
        Scene _scene;
		std::unique_ptr<Camera> _camera;
		bool _isCameraRotating = false;
		float _backgroundColor[4];
		glm::mat4 projection;


	};

}
