#pragma once

#include <vector>
#include <memory>
#include "Engine/Objects/Mesh.h"
#include "OBJ_Loader.h"

namespace Engine {
    class Model {
    public:
        Model(std::string name, std::string path) :_name(name){
            loadModel(path);
        }

        Model() = default;

        Model(const Model &) = delete;

        Model(Model &&) = default;

        Model &operator=(const Model &) = delete;

        Model &operator=(Model &&) = default;

        void AddMesh(Mesh &&mesh) { _meshes.push_back(std::move(mesh)); }

        void Draw(ShaderProgram &shader);

        void ImGuiRender();

        const std::string &GetName() const { return _name; }

        void SetName(const std::string &name) { _name = name; }

    private:
        void loadModel(std::string path);

        Mesh processMesh(const objl::Mesh &mesh, const objl::Loader &loader);

        Transform _transform;
        std::string _name;
        std::vector<Mesh> _meshes;
        std::string _directory;
    };
}