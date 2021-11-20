#pragma once
#include "Engine/Objects/Model.h"
namespace Engine {
    class Light {
    public:
        Light();
        Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

        void InitShader(ShaderProgram &program);

        void Draw(ShaderProgram &program);
        void ImGuiRender();
        const Transform GetTransform() const {return cube.GetTransform();}
        void SetScale(const glm::vec3 &scale){cube.SetScale(scale);}

        void SetRotation(const glm::vec3 &rotation){cube.SetRotation(rotation);}

        void SetTranslation(const glm::vec3 &translation){cube.SetTranslation(translation);}
        glm::vec3 _position, _ambient, _diffuse, _specular;
        Model cube;
    };
}