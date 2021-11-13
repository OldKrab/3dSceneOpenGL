#pragma once
#include <iostream>

struct GLFWwindow;
namespace Engine {
    class Window {
    public:
        Window(int width, int height, const char *title);

        int Start();

    private:
        int Init();
        int ImGuiInit();

        void Render();
        void OnUpdate();
        void ImGuiRender(); 
        int _width, _height;
        std::string  _title;
        GLFWwindow *_window;
        float _backgroundColor[4];
    };

}
