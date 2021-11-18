#pragma once


#include <glm/ext/matrix_float4x4.hpp>

namespace Engine {

    class Transform {
    public:
        Transform();

        void SetScale(const glm::vec3 &scale);

        void SetRotation(const glm::vec3 &rotation);

        void SetTranslation(const glm::vec3 &translation);

        const glm::vec3 &GetScale() const { return _scale; }

        const glm::vec3 &GetTranslation() const { return _translation; }

        const glm::vec3 &GetRotation() const { return _rotation; }

        void ImGuiRender();

        glm::mat4 GetMatrix() const;

    private:

        glm::vec3 _scale = glm::vec3(1.f, 1.f, 1.f);
        glm::vec3 _translation = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 _rotation = glm::vec3(0.f, 0.f, 0.f);

        mutable bool _isModified;
        mutable glm::mat4 _cachedTrans;
    };

}
