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


    class Mesh  {
    public:
        Mesh(std::string name, std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::unique_ptr<Texture> texture);
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::unique_ptr<Texture> texture);

        void Draw(ShaderProgram &shader);
        void ImGuiRender();

        const std::string& GetName() const {return _name;}
        void SetName(const std::string& name)  { _name = name;}
    private:
        void SetupMesh();
        Transform _transform;
        std::string _name;
        std::vector<Vertex> _vertices;
        std::vector<GLuint> _indexes;
        std::unique_ptr<Texture> _texture;
        std::unique_ptr<VertexArray> _vao;
        std::unique_ptr<VertexBuffer> _vbo;
        std::unique_ptr<IndexBuffer> _ibo;
    };


}
