#pragma once


#include <Engine/Shader/ShaderProgram.h>
#include <memory>
#include <vector>
#include "Mesh.h"
#include "Model.h"

namespace Engine {

	class Scene {
	public:
		Scene() = default;
        Scene(const Scene&) = delete;
        Scene(Scene&&) = default;
        Scene operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = default;
		void Draw(ShaderProgram &shader);
		void ImGuiRender();
		void AddModel(Model&& model);
	private:
		std::vector<Model> _models;
	};

}
