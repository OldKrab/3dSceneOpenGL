#include <Engine/Shader/ShaderProgram.h>
#include <vector>
#include <Engine/Objects/Mesh.h>
#include "Engine/Objects/Light.h"

namespace Engine {

    void Light::InitShader(ShaderProgram &program) {
        program.SetUniformVec3("light.position", cube.GetTransform().GetTranslation());
        program.SetUniformVec3("light.ambient", _ambient);
        program.SetUniformVec3("light.diffuse", _diffuse);
        program.SetUniformVec3("light.specular", _specular);
    }

    Light::Light() : Light({0, 100, 0}, {0.2, 0.2, 0.2}, {0.5, 0.5, 0.5}, {1, 1, 1}) {

    }

    Engine::Mesh CreateLightCube() {
        std::vector<Engine::Vertex> vertexes
                {
                        {{-0.5f, -0.5f, -0.5f}, {0, 0, 0}, {0.25f, 0.5f}},
                        {{-0.5f, 0.5f,  -0.5f}, {0, 0, 0}, {0.25f, 0.75f}},
                        {{0.5f,  0.5f,  -0.5f}, {0, 0, 0}, {0.5f,  0.75f}},
                        {{0.5f,  -0.5f, -0.5f}, {0, 0, 0}, {0.5f,  0.5f}},

                        {{-0.5f, -0.5f, 0.5f},  {0, 0, 0}, {0,     0.5f}},
                        {{-0.5f, -0.5f, 0.5f},  {0, 0, 0}, {0.25f, 0.25f}},
                        {{-0.5f, -0.5f, 0.5f},  {0, 0, 0}, {1.f,   0.5f}},

                        {{-0.5f, 0.5f,  0.5f},  {0, 0, 0}, {0,     0.75f}},
                        {{-0.5f, 0.5f,  0.5f},  {0, 0, 0}, {0.25f, 1.f}},
                        {{-0.5f, 0.5f,  0.5f},  {0, 0, 0}, {1.f,   0.75f}},

                        {{0.5f,  0.5f,  0.5f},  {0, 0, 0}, {0.5f,  1.f}},
                        {{0.5f,  0.5f,  0.5f},  {0, 0, 0}, {0.75f, 0.75f}},

                        {{0.5f,  -0.5f, 0.5f},  {0, 0, 0}, {0.5f,  0.25f}},
                        {{0.5f,  -0.5f, 0.5f},  {0, 0, 0}, {0.75f, 0.5f}}
                };

        std::vector<GLuint> indexes{
                1, 3, 0, 1, 3, 2, 2, 13, 3, 2, 13, 11, 11, 6, 13, 11, 6, 9, 7, 0, 4, 7, 0, 1, 8, 2, 1, 8, 2, 10, 0, 12,
                5, 0, 12, 3
        };

        auto mat = std::make_shared<Engine::Material>();
        return Engine::Mesh(vertexes, indexes, std::make_shared<Engine::Material>());
    }

    Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
            : _position(position), _ambient(ambient), _diffuse(diffuse), _specular(specular), cube("light") {
        cube.AddMesh(CreateLightCube());

    }

    void Light::Draw(ShaderProgram &program) {
        cube.Draw(program);
    }

    void Light::ImGuiRender() {
        cube.ImGuiRender();
    }
}