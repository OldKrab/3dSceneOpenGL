#pragma once

namespace Engine {
    static const char* vertexShaderSource =
            R"(#version 460
            layout(location = 0) in vec3 vertexPosition;
			layout(location = 1) in vec3 normal;
			layout(location = 2) in vec2 texPoints;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

            out vec3 color;
            out vec2 texPoint;

            void main() {
				texPoint = texPoints;   
				gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
            })";

    static const char* fragmentShaderSource =
            R"(#version 460
			in vec2 texPoint;

			uniform sampler2D texId;

			out vec4 fragColor;

            void main() {
               fragColor = texture(texId, texPoint);
            })";
}