#include "Engine/Window.h"

#include <iostream>
#include "Engine/Shader/shaders.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

    std::unique_ptr<Mesh> CreateCube() {
        std::vector<Vertex> vertexes
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


        auto texture = std::make_unique<Texture>("assets/tex2.jpg");
        texture->SetParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        return std::make_unique<Mesh>(vertexes, indexes, std::move(texture));
    }


    Window::Window(int width, int height, const char *title)
            : _width(width), _height(height), _title(title), _window(nullptr), _backgroundColor{1, 0, 1, 1} {
        GlfwInit();
        GladInit();
        Init();
        ImGuiInit();

    }

    ///////////////////////////////////////////
    int Window::Start() {
        while (!glfwWindowShouldClose(_window)) {
            OnUpdate();
            Render();
            ImGuiRender();
            glfwSwapBuffers(_window);
        }

        glfwTerminate();
        return 0;
    }


    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 1.0f, 100.0f);

    static glm::vec3 _scale = glm::vec3(1.f, 1.f, 1.f);
    static glm::vec3 _translation = glm::vec3(0.f, 0.f, 0.f);
    static glm::vec3 _rotation = glm::vec3(0.f, 0.f, 0.f);
    static bool _rotating = false;

    ///////////////////////////////////////////
    void Window::Render() {
        glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2], _backgroundColor[3]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _shaderProgram->Use();

        _shaderProgram->SetUniformMatrix4fv("view", view);
        _shaderProgram->SetUniformMatrix4fv("projection", projection);
        _cube->Draw(*_shaderProgram);
    }

    ///////////////////////////////////////////
    void Window::OnUpdate() {
        glfwPollEvents();
        static int fps = 0;
        static double time = 0;
        static double prevTime = 0;

        double curTime = glfwGetTime();
        double deltaTime = curTime - prevTime;
        prevTime = curTime;

        fps++;
        time += deltaTime;
        if (time > 1) {
            time -= 1.;
            glfwSetWindowTitle(_window, (std::string("FPS:") + std::to_string(fps)).c_str());
            fps = 0;
        }

        if (_rotating)
            _rotation[1] += 1.f * (float) deltaTime;

        _cube->SetRotation(_rotation);
        _cube->SetTranslation(_translation);
        _cube->SetScale(_scale);

    }

    ///////////////////////////////////////////
    int Window::Init() {
        _shaderProgram = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
        _cube = CreateCube();
        view = glm::translate(view, {0, 0, -3});
        return 0;
    }

    ///////////////////////////////////////////
    int Window::GlfwInit() {
        if (!glfwInit())
            return -1;

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (!_window) {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(_window);

        glfwSetFramebufferSizeCallback(_window,
                                       [](GLFWwindow *window, int width, int height) {
                                           glViewport(0, 0, width, height);
                                       });


        return 0;
    }

    ///////////////////////////////////////////
    int Window::GladInit() {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            return -1;
        }
        glEnable(GL_DEPTH_TEST);
        return 0;
    }

    ///////////////////////////////////////////
    int Window::ImGuiInit() const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(_window, true);
        ImGui_ImplOpenGL3_Init();
        return 0;
    }

    ///////////////////////////////////////////
    void Window::ImGuiRender() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();

        ImGui::Begin("Debug");
        ImGui::ColorEdit4("Background Color", _backgroundColor);
        ImGui::DragFloat3("Scale", &_scale[0], 0.01f);
        ImGui::DragFloat3("Translation", &_translation[0], 0.01f);
        ImGui::DragFloat3("Rotation", &_rotation[0], 0.01f);
        ImGui::Checkbox("Rotating", &_rotating);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
