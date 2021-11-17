#include "Engine/Window.h"
#include <memory>
#include <iostream>


std::unique_ptr<Engine::Mesh> CreateCube() {
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


    auto texture = std::make_unique<Engine::Texture>("assets/tex2.jpg");
    texture->SetParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return std::make_unique<Engine::Mesh>("Some Head", vertexes, indexes, std::move(texture));
}

int main() {
	try{

	auto window = std::make_unique<Engine::Window>(1600, 900, "Test");
    Engine::Scene scene;
    scene.AddMesh(CreateCube());
    window->SetScene(std::move(scene));
    window->Start();
	}catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

