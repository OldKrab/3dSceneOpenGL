#include <Engine/Shader/ShaderProgram.h>
#include "Engine/Objects/Model.h"

namespace Engine {

    void Model::Draw(ShaderProgram &shader) {
        auto debug = _transform.GetMatrix();
        shader.SetUniformMatrix4fv("model", debug);
        for (auto &&mesh: _meshes) {
            mesh.Draw(shader);
        }
    }

    void Model::ImGuiRender() {
        _transform.ImGuiRender();

    }

    void Model::loadModel(std::string path) {
        objl::Loader loader;
        if(!loader.LoadFile(path))
            throw std::runtime_error("Couldn't load model : " + path);
        _directory = path.substr(0, path.find_last_of('/') + 1);
        for (auto &&mesh: loader.LoadedMeshes)
            _meshes.push_back(processMesh(mesh, loader));

    }


    Mesh Model::processMesh(const objl::Mesh &mesh, const objl::Loader &loader) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for (auto &&objVertex: mesh.Vertices) {
            Vertex vertex;
            // Обрабатываем координаты вершин, нормали и текстурные координаты
            glm::vec3 vector;
            vector.x = objVertex.Position.X;
            vector.y = objVertex.Position.Y;
            vector.z = objVertex.Position.Z;
            vertex.Position = vector;
            vector.x = objVertex.Normal.X;
            vector.y = objVertex.Normal.Y;
            vector.z = objVertex.Normal.Z;
            vertex.Normal = vector;
            glm::vec2 vec2;
            vec2.x = objVertex.TextureCoordinate.X;
            vec2.y = objVertex.TextureCoordinate.Y;
            vertex.TexCoords = vec2;
            vertices.push_back(vertex);
        }
        // Обрабатываем индексы
        indices = mesh.Indices;
        // Обрабатываем материал
        if (mesh.MeshMaterial.map_Kd != "")
            textures.emplace_back(_directory + mesh.MeshMaterial.map_Kd);

        return Mesh(vertices, indices, std::move(textures));
    }




}