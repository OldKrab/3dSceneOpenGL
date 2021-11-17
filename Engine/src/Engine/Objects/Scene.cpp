#include "Engine/Texture.h"
#include <Engine/Objects/Scene.h>
#include <imgui.h>

#include "stb_image.h"

namespace Engine {
    void Scene::Draw(ShaderProgram &shader) {
        for (auto &&mesh: _models)
            mesh.Draw(shader);
    }

    void Scene::ImGuiRender() {
        if (ImGui::CollapsingHeader("Meshes")) {
            ImGui::Indent();
            for (int i = 0; i < _models.size(); i++)
                if (ImGui::TreeNode(_models[i].GetName().c_str())) {
                    _models[i].ImGuiRender();
                    ImGui::TreePop();
                }
            ImGui::Unindent();
        }
    }

    void Scene::AddModel(Model &&model) {
        _models.push_back(std::move(model));
    }
}
