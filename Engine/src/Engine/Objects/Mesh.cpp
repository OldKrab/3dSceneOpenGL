#include <utility>
#include <iostream>

#include "Engine/Objects/Mesh.h"

namespace Engine {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::unique_ptr<Texture> texture)
            : vertices(std::move(vertices)), indexes(std::move(indexes)), _texture(std::move(texture)) {
        SetupMesh();
    }

    void Mesh::Draw(ShaderProgram &shader) {
        _texture->Bind();
        _vao->Bind();
        auto debug = GetTransform();
        shader.SetUniformMatrix4fv("model", debug);

        glDrawElements(GL_TRIANGLES, (GLsizei) indexes.size(), GL_UNSIGNED_INT, 0);
    }

    void Mesh::SetupMesh() {
        _vao = std::make_unique<VertexArray>();
        BufferLayout layout({{GL_FLOAT, 3},
                             {GL_FLOAT, 3},
                             {GL_FLOAT, 2}});
        _vao->Bind();
        _vbo = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex), layout,
                                              BufferUsage::Static);
        _ibo = std::make_unique<IndexBuffer>(indexes.data(), indexes.size() * sizeof(Vertex), indexes.size(),
                                             BufferUsage::Static);

        _vao->AddVertexBuffer(*_vbo);
        _vao->SetIndexBuffer(*_ibo);
    }
}
