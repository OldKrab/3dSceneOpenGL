#include "Engine/Texture.h"
#include <Engine/Objects/Scene.h>
#include <imgui.h>
#include <Engine/Objects/Light.h>

#include "stb_image.h"

namespace Engine {
    void Scene::Draw(ShaderProgram &shader, ShaderProgram &lightShader) {
        _light.InitShader(shader);
        _isLightInited = true;
        for (auto &&mesh: _models)
            mesh.Draw(shader);
        lightShader.Use();
        _light.Draw(lightShader);
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
        if (ImGui::CollapsingHeader("Light")) {
            ImGui::Indent();
            _light.ImGuiRender();
            ImGui::Unindent();
        }
    }

    void Scene::AddModel(Model &&model) {
        _nameToModelMap[model.GetName()] = _models.size();
        _models.push_back(std::move(model));
    }

    std::ostream &operator<<(std::ostream &out, const glm::vec3 &v) {
        out << v.x << ' ' << v.y << ' ' << v.z;
        return out;
    }

    std::istream &operator>>(std::istream &in, glm::vec3 &v) {
        in >> v.x >> v.y >> v.z;
        return in;
    }

    void Scene::Save(std::string path) {
        std::ofstream fout(path);
        for (auto &&model: _models) {
            fout << model.GetName() << std::endl;
            fout << model.GetTransform().GetRotation() << std::endl;
            fout << model.GetTransform().GetScale() << std::endl;
            fout << model.GetTransform().GetTranslation() << std::endl;
        }
        fout << "light" << std::endl;
        fout << _light.GetTransform().GetRotation() << std::endl;
        fout << _light.GetTransform().GetScale() << std::endl;
        fout << _light.GetTransform().GetTranslation() << std::endl;
    }

    void Scene::LoadSave(std::string path) {
        std::ifstream fin(path);
        if (!fin.is_open())
            return;
        std::string name;
        fin >> name;
        while (!fin.eof()) {
            auto it = _nameToModelMap.find(name);
            if (it != _nameToModelMap.end()) {
                glm::vec3 rot, sc, tr;
                fin >> rot >> sc >> tr;
                _models[it->second].SetRotation(rot);
                _models[it->second].SetScale(sc);
                _models[it->second].SetTranslation(tr);
            } else if (name == "light") {
                glm::vec3 rot, sc, tr;
                fin >> rot >> sc >> tr;
                _light.SetRotation(rot);
                _light.SetScale(sc);
                _light.SetTranslation(tr);
            }
            fin >> name;
        }
    }

    void Scene::SetLight(Light model) {
        _light = std::move(model);
        _isLightInited = false;
    }
}
