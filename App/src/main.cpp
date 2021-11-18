#include "Engine/Window.h"
#include <memory>
#include <iostream>


Engine::Mesh CreateCube() {
    std::vector<Engine::Vertex> vertexes
            {
                    {{-0.5f, -0.5f, -0.5f}, {0, 0, 0}, {0.f, 0.f}},
                    {{-0.5f, 0.5f,  -0.5f}, {0, 0, 0}, {0.f, 1.f}},
                    {{0.5f,  0.5f,  -0.5f}, {0, 0, 0}, {1.f,  1.f}},
                    {{0.5f,  -0.5f, -0.5f}, {0, 0, 0}, {1.f,  0.f}},
            };

    std::vector<GLuint> indexes{
            1, 3, 0, 1, 3, 2
    };

    std::vector<Engine::Texture> textures;
    auto texture = Engine::Texture("assets/forestBack.png");
    texture.SetParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    textures.push_back(std::move(texture));
    return Engine::Mesh("Some Head", vertexes, indexes, std::move(textures));
}

int main() {
    try {
        std::string savePath = "D:\\source\\c++\\3dSceneOpenGL\\App\\assets\\saves\\save1";
        auto window = std::make_unique<Engine::Window>(1600, 900, "Test");
        auto scene = std::make_shared<Engine::Scene>();

        Engine::Model forestBack("forestBack");
        forestBack.AddMesh(CreateCube());
        scene->AddModel(std::move(forestBack));
        scene->AddModel(Engine::Model("mister", "assets/hitler/hitler.obj"));
        scene->AddModel(Engine::Model("grass", "assets/grass/10450_Rectangular_Grass_Patch_v1_iterations-2.obj"));
        scene->AddModel(Engine::Model("grass2", "assets/grass/10450_Rectangular_Grass_Patch_v1_iterations-2.obj"));
        scene->AddModel(Engine::Model("forest", "assets/forest/Bush 6.obj"));
        scene->AddModel(Engine::Model("OldTractor", "assets/Tractor1/tractor.obj"));
        scene->AddModel(Engine::Model("NewTractor", "assets/Tractor2/tractor.obj"));
        scene->LoadSave(savePath);
        window->SetScene(scene);
        window->Start();
        scene->Save(savePath);
    } catch (std::exception &e) {
        std::cout << e.what();
    }
}

