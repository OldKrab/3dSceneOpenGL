#pragma once

#include <memory>
#include <vector>

#include "Engine/Texture.h"
#include "glad/glad.h"
#include "Engine/Shader/ShaderProgram.h"
#include "Engine/Shader/VertexArray.h"
#include "Engine/Objects/Transform.h"
#include "Engine/Objects/Camera.h"


namespace Engine {


    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };


    class Mesh {
    public:
        Mesh(std::string name, std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::vector<Texture> texture);

        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::vector<Texture> texture);

        Mesh(const Mesh &) = delete;

        Mesh(Mesh &&other) noexcept;

        Mesh operator=(const Mesh &) = delete;

        Mesh& operator=(Mesh &&other) noexcept;

        void Draw(ShaderProgram &shader);


    private:
        void Swap(Mesh& other);

        void SetupMesh();


        std::vector<Vertex> _vertices;
        std::vector<GLuint> _indexes;
        std::vector<Texture> _textures;
        std::unique_ptr<VertexArray> _vao;
        std::unique_ptr<VertexBuffer> _vbo;
        std::unique_ptr<IndexBuffer> _ibo;
    };


}
