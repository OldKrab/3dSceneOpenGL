#include <utility>
#include <iostream>
#include <imgui.h>

#include "Engine/Objects/Mesh.h"

namespace Engine {
    Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<GLuint> indexes,
               std::vector<Texture> texture)
            : _vertices(std::move(vertices)), _indexes(std::move(indexes)),
              _textures(std::move(texture)) {
        SetupMesh();
    }

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::vector<Texture> texture)
            : Mesh("NoName", std::move(vertices), std::move(indexes), std::move(texture)) {}

    void Mesh::Draw(ShaderProgram &shader) {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for (unsigned int i = 0; i < _textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // активируем соответствующий текстурный юнит перед привязкой
            // Получаем номер текстуры (значение N в diffuse_textureN)
            std::string number;
            std::string name = _textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            shader.SetFloat(("material." + name + number).c_str(), i);
            _textures[i].Bind();
        }
        glActiveTexture(GL_TEXTURE0);
        _vao->Bind();


        glDrawElements(GL_TRIANGLES, (GLsizei) _indexes.size(), GL_UNSIGNED_INT, 0);
    }

    void Mesh::SetupMesh() {
        _vao = std::make_unique<VertexArray>();
        BufferLayout layout({{GL_FLOAT, 3},
                             {GL_FLOAT, 3},
                             {GL_FLOAT, 2}});
        _vao->Bind();
        _vbo = std::make_unique<VertexBuffer>(_vertices.data(), _vertices.size() * sizeof(Vertex), layout,
                                              BufferUsage::Static);
        _ibo = std::make_unique<IndexBuffer>(_indexes.data(), _indexes.size() * sizeof(GLuint), _indexes.size(),
                                             BufferUsage::Static);

        _vao->AddVertexBuffer(*_vbo);
        _vao->SetIndexBuffer(*_ibo);
    }


    Mesh::Mesh(Mesh &&other) noexcept {
        Swap(other);
    }

    Mesh &Mesh::operator=(Mesh &&other) noexcept {
        Mesh temp(std::move(other));
        Swap(temp);
        return *this;
    }

    void Mesh::Swap(Mesh &other) {
        std::swap(_vertices, other._vertices);
        std::swap(_indexes, other._indexes);
        std::swap(_textures, other._textures);
        std::swap(_vao, other._vao);
        std::swap(_vbo, other._vbo);
        std::swap(_ibo, other._ibo);
    }


}
