#include <utility>
#include <iostream>
#include <imgui.h>

#include "Engine/Objects/Mesh.h"

namespace Engine {
    Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<GLuint> indexes,
               std::unique_ptr<Texture> texture)
            : _name(std::move(name)), _vertices(std::move(vertices)), _indexes(std::move(indexes)),
              _texture(std::move(texture)) {
        SetupMesh();
    }

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indexes, std::unique_ptr<Texture> texture)
            : Mesh("NoName", std::move(vertices), std::move(indexes), std::move(texture)) {}

    void Mesh::Draw(ShaderProgram &shader) {
        _texture->Bind();
        _vao->Bind();
        auto debug = _transform.GetMatrix();
        shader.SetUniformMatrix4fv("model", debug);

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
        _ibo = std::make_unique<IndexBuffer>(_indexes.data(), _indexes.size() * sizeof(Vertex), _indexes.size(),
                                             BufferUsage::Static);

        _vao->AddVertexBuffer(*_vbo);
        _vao->SetIndexBuffer(*_ibo);
    }

    void Mesh::ImGuiRender() {
        if (ImGui::TreeNode(_name.c_str())) {
            _transform.ImGuiRender();
            ImGui::TreePop();
        }
    }


}
