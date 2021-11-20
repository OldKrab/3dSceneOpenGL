#include <utility>
#include <iostream>

#include "Engine/Objects/Mesh.h"

namespace Engine {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indexes,
               std::shared_ptr<Material> material)
            : _vertices(std::move(vertices)), _indexes(std::move(indexes)), _material(material) {
        SetupMesh();
    }

    void Mesh::Draw(ShaderProgram &shader) {
        shader.SetUniformFloat("material.diffuse", 0);
        shader.SetUniformFloat("material.specular", 1);
        if(_material->diffuseTex != nullptr) {
            glActiveTexture(GL_TEXTURE0);
            _material->diffuseTex->Bind();
        }
        if(_material->specularTex != nullptr) {
            glActiveTexture(GL_TEXTURE1);
            _material->specularTex->Bind();
        }
        //glBindTexture(GL_TEXTURE_2D, 0);
        shader.SetUniformFloat("material.shininess", _material->shininess);

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
        std::swap(_material, other._material);
        std::swap(_vao, other._vao);
        std::swap(_vbo, other._vbo);
        std::swap(_ibo, other._ibo);
    }


}
