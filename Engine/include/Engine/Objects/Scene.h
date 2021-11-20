#pragma once

#include <Engine/Shader/ShaderProgram.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Mesh.h"
#include "Model.h"
#include "Light.h"

namespace Engine {

	class Scene {
	public:
		Scene() = default;
        Scene(const Scene&) = delete;
        Scene(Scene&&) = default;
        Scene operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = default;
		void Draw(ShaderProgram &shader, ShaderProgram &lightShader);
		void ImGuiRender();
		void AddModel(Model&& model);
		void SetLight(Light model);

		void Save(std::string path);
		void LoadSave(std::string path);

	private:
		std::vector<Model> _models;
		Light _light;
		bool _isLightInited = false;
		std::unordered_map<std::string, int> _nameToModelMap;
	};

}
