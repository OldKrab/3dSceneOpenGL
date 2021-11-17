#include "Engine/Window.h"
#include <memory>
#include <iostream>


Engine::Mesh CreateCube() {
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

    std::vector<Engine::Texture> textures;
    auto texture = Engine::Texture("assets/tex2.jpg");
    texture.SetParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    textures.push_back(std::move(texture));
    return Engine::Mesh("Some Head", vertexes, indexes, std::move(textures));
}

int main() {
    try {

        auto window = std::make_unique<Engine::Window>(1600, 900, "Test");
        Engine::Scene scene;

        scene.AddModel(Engine::Model("mister", "assets/hitler/hitler.obj"));
        scene.AddModel(Engine::Model("grass", "assets/grass/10450_Rectangular_Grass_Patch_v1_iterations-2.obj"));
        window->SetScene(std::move(scene));
        window->Start();
    } catch (std::exception &e) {
        std::cout << e.what();
    }
}

