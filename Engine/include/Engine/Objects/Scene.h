#pragma once


#include <Engine/Shader/ShaderProgram.h>
#include <memory>
#include <vector>
#include "Mesh.h"

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
		void AddMesh(std::unique_ptr<Mesh>&& mesh);
	private:
		std::vector<std::unique_ptr<Mesh>> _meshes;
	};

}
