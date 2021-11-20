#include "Engine/Window.h"

#include <iostream>
#include "Engine/Shader/shaders.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

    Window::Window(int width, int height, const char *title)
            : _width(width), _height(height), _title(title), _window(nullptr), _backgroundColor{0, 188.f/255.f, 1, 1} {
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


    ///////////////////////////////////////////
    void Window::Render() {
        glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2], _backgroundColor[3]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _shaderProgramLight->Use();
        _shaderProgramLight->SetUniformMat4("view", _camera.GetView());
        _shaderProgramLight->SetUniformMat4("projection", projection);
        _shaderProgram->Use();
        _shaderProgram->SetUniformMat4("view", _camera.GetView());
        _shaderProgram->SetUniformMat4("projection", projection);
        _shaderProgram->SetUniformVec3("viewPos", _camera.GetPosition());

        _scene->Draw(*_shaderProgram, *_shaderProgramLight);
    }

    ///////////////////////////////////////////
    void Window::OnUpdate() {
        glfwPollEvents();

        static float time = 0;
        static float prevTime = 0;
        float curTime = glfwGetTime();
        float deltaTime = curTime - prevTime;
        prevTime = curTime;

        UpdateCameraPos(deltaTime);

        static int fps = 0;
        fps++;
        time += deltaTime;
        if (time > 1) {
            time -= 1.;
            glfwSetWindowTitle(_window, (std::string("FPS:") + std::to_string(fps)).c_str());
            fps = 0;
        }

        // _cube->SetRotation(_rotation);
        // _cube->SetTranslation(_translation);
        // _cube->SetScale(_scale);

    }

    ///////////////////////////////////////////
    int Window::Init() {
        _shaderProgram = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
        _shaderProgramLight = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderLightSource);
        _camera.MovePosition({0, 0, -3});
        SetProjection(_width, _height);

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
        glfwSetWindowUserPointer(_window, this);

        glfwSetFramebufferSizeCallback(_window,
                                       [](GLFWwindow *window, int width, int height) {
                                           auto pw = (Window *) glfwGetWindowUserPointer(window);
                                           if (height != 0)
                                               pw->SetProjection(width, height);
                                           glViewport(0, 0, width, height);
                                       });

        glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            auto pw = (Window *) glfwGetWindowUserPointer(window);
            pw->KeyCallback(window, key, scancode, action, mods);
        });
        glfwSetMouseButtonCallback(_window, [](GLFWwindow *window, int button, int action, int mods) {
            auto pw = (Window *) glfwGetWindowUserPointer(window);
            pw->MouseButtonCallback(window, button, action, mods);
        });
        glfwSetCursorPosCallback(_window, [](GLFWwindow *window, double xpos, double ypos) {
            auto pw = (Window *) glfwGetWindowUserPointer(window);
            pw->MousePosCallback(window, xpos, ypos);
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

        // ImGui::ShowDemoWindow();

        ImGui::Begin("Debug");
        ImGui::ColorEdit4("Background Color", _backgroundColor);

        _scene->ImGuiRender();
        _camera.ImGuiRender();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ///////////////////////////////////////////
    void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        //nothing
    }

    void Window::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            _isCameraRotating = true;
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
            _isCameraRotating = false;

    }

    ///////////////////////////////////////////
    void Window::MousePosCallback(GLFWwindow *window, double xpos, double ypos) {
        static bool firstMouse = true;
        if (_isCameraRotating) {
            static double lastX, lastY;
            if (firstMouse) {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            auto xoffset = (float) (xpos - lastX);
            auto yoffset = (float) (lastY - ypos);

            lastX = xpos;
            lastY = ypos;

            _camera.MoveDirection(xoffset, yoffset);
        } else
            firstMouse = true;
    }

    ///////////////////////////////////////////
    void Window::UpdateCameraPos(float delta) {
        glm::vec3 position(0, 0, 0);
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            position.z += 1;
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            position.z -= 1;
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            position.x -= 1;
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            position.x += 1;
        if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position.y += 1;
        if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            position.y -= 1;

        if (glm::abs(glm::length(position)) > 1e-5)
            _camera.MovePosition(glm::normalize(position) * delta);
    }

    ///////////////////////////////////////////
    void Window::SetProjection(int width, int height) {
        projection = glm::perspective(glm::radians(45.0f),
                                      (float) width / (float) height, 0.01f,
                                      1000.0f);
        glm::
    }

    void Window::SetScene(std::shared_ptr<Scene> scene) {
        _scene = std::move(scene);

    }


}
