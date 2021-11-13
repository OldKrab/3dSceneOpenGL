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

        int _width, _height;
        std::string  _title;
        GLFWwindow *_window;
    };

}
