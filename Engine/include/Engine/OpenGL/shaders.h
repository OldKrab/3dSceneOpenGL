#pragma once

namespace Engine {
    static const char* vertexShaderSource =
            "#version 460\n"
            "layout(location = 0) in vec3 vertexPosition;"
            "layout(location = 1) in vec3 vertexColor;"
            "out vec3 color;"
            "void main() {"
            "   color = vertexColor;"
            "   gl_Position = vec4(vertexPosition, 1.0);"
            "}";

    static const char* fragmentShaderSource =
            "#version 460\n"
            "in vec3 color;"
            "out vec4 fragColor;"
            "void main() {"
            "   fragColor = vec4(color, 1.0);"
            "}";
}