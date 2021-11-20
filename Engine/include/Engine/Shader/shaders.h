#pragma once

namespace Engine {
    static const char *vertexShaderSource =
            R"( #version 330 core
                layout (location = 0) in vec3 aPos;
                layout (location = 1) in vec3 aNormal;
                layout (location = 2) in vec2 aTexCoords;

                out vec3 FragPos;
                out vec3 Normal;
                out vec2 TexCoords;

                uniform mat4 model;
                uniform mat4 view;
                uniform mat4 projection;

                void main()
                {
                    FragPos = vec3(model * vec4(aPos, 1.0));
                    Normal = mat3(transpose(inverse(model))) * aNormal;
                    TexCoords = aTexCoords;

                    gl_Position = projection * view * vec4(FragPos, 1.0);
                })";

    static const char *fragmentShaderSource =
            R"(#version 330 core
            out vec4 FragColor;

            struct Material {
                sampler2D diffuse;
                sampler2D specular;
                float shininess;
            };

            struct Light {
                vec3 position;
                vec3 ambient;
                vec3 diffuse;
                vec3 specular;
            };

            in vec3 FragPos;
            in vec3 Normal;
            in vec2 TexCoords;

            uniform vec3 viewPos;
            uniform Material material;
            uniform Light light;

            void main()
            {
                if(texture(material.diffuse, TexCoords).a < 0.5)
                    discard;
                // Окружающая составляющая
                vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
                // Диффузная составляющая
                vec3 norm = normalize(Normal);
                vec3 lightDir = normalize(light.position - FragPos);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

                // Отраженная составляющая
                vec3 viewDir = normalize(viewPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
                vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

                vec3 result = ambient + diffuse + specular;
                FragColor = vec4(result, 1.0f);
            } )";

    static const char *vertexShaderLightSource =
            R"( #version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
})";

    static const char *fragmentShaderLightSource =
            R"(#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // устанавливаем значения всех 4-х компонентов вектора равными 1.0
})";


}