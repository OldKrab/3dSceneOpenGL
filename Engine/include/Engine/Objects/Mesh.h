#pragma once

#include <memory>
#include <vector>

#include "Engine/Texture.h"
#include "glad/glad.h"
#include "Engine/Shader/ShaderProgram.h"
#include "Engine/Shader/VertexArray.h"
#include "Engine/Objects/Transformable.h"


namespace Engine {


    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };


    class Mesh : public Transformable {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::unique_ptr<Texture> texture);

        void Draw(ShaderProgram &shader);

        std::vector<Vertex> vertices;
        std::vector<GLuint> indexes;
        std::unique_ptr<Texture> _texture;

    private:
        void SetupMesh();

        std::unique_ptr<VertexArray> _vao;
        std::unique_ptr<VertexBuffer> _vbo;
        std::unique_ptr<IndexBuffer> _ibo;
    };


}
