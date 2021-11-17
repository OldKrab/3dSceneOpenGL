#include "Engine/Texture.h"
#include <Engine/Objects/Scene.h>
#include <imgui.h>

#include "stb_image.h"

namespace Engine {
    void Scene::Draw(ShaderProgram &shader) {
        for (auto &&mesh: _meshes)
            mesh->Draw(shader);
    }

    void Scene::ImGuiRender() {
        if (ImGui::CollapsingHeader("Meshes")) {
            for (auto &&mesh: _meshes)
                mesh->ImGuiRender();
        }
    }

    void Scene::AddMesh(std::unique_ptr<Mesh>&& mesh) {
        _meshes.push_back(std::move(mesh));
    }
}
