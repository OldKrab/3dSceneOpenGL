#include "Engine/Window.h"
#include <memory>
#include <iostream>


Engine::Mesh CreateBack() {
    std::vector<Engine::Vertex> vertexes
            {
                    {{-0.5f, -0.5f, -0.5f}, {0, 0, 1}, {0.f, 0.f}},
                    {{-0.5f, 0.5f,  -0.5f}, {0, 0, 1}, {0.f, 1.f}},
                    {{0.5f,  0.5f,  -0.5f}, {0, 0, 1}, {1.f, 1.f}},
                    {{0.5f,  -0.5f, -0.5f}, {0, 0, 1}, {1.f, 0.f}},
            };

    std::vector<GLuint> indexes{
            1, 3, 0, 1, 3, 2
    };
    auto mat = std::make_shared<Engine::Material>();
    mat->diffuseTex = std::make_shared<Engine::Texture>("assets/forestBack.png");
    //mat->specularTex = std::make_shared<Engine::Texture>("assets/white.jpg");
    return Engine::Mesh(vertexes, indexes, mat);
}



int main() {
    try {
        std::string savePath = "D:\\source\\c++\\3dSceneOpenGL\\App\\assets\\saves\\save1";
        auto window = std::make_unique<Engine::Window>(1600, 900, "Test");
        auto scene = std::make_shared<Engine::Scene>();

        Engine::Model forestBack("forestBack");
        forestBack.AddMesh(CreateBack());
        scene->AddModel(std::move(forestBack));
        scene->AddModel(Engine::Model("grass", "assets/grass/10450_Rectangular_Grass_Patch_v1_iterations-2.obj"));
        scene->AddModel(Engine::Model("grass2", "assets/grass/10450_Rectangular_Grass_Patch_v1_iterations-2.obj"));
        scene->AddModel(Engine::Model("forest", "assets/forest/Bush 6.obj"));
        scene->AddModel(Engine::Model("mister", "assets/mister/mister.obj"));
        scene->AddModel(Engine::Model("mister2", "assets/some/body2.obj"));
        scene->AddModel(Engine::Model("OldTractor", "assets/Tractor1/tractor.obj"));
        scene->AddModel(Engine::Model("NewTractor", "assets/Tractor2/tractor.obj"));
        scene->SetLight(Engine::Light({1.2f, 100.0f, 2.0f}, {0.4,0.4,0.4}, {1,1,1}, {1,1,1}));
        scene->LoadSave(savePath);
        window->SetScene(scene);
        window->Start();
        scene->Save(savePath);
    } catch (std::exception &e) {
        std::cout << e.what();
    }
}

