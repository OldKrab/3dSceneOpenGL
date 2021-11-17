#pragma once


#include <glm/ext/matrix_float4x4.hpp>

namespace Engine {

    class Transformable {
    public:
        Transformable();

        void SetScale(const glm::vec3& scale);
        void SetRotation(const glm::vec3& rotation);
        void SetTranslation(const glm::vec3& translation);

        glm::mat4 GetTransform() const;
    private:

        glm::vec3 _scale = glm::vec3(1.f, 1.f, 1.f);
        glm::vec3 _translation = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 _rotation = glm::vec3(0.f, 0.f, 0.f);

        mutable bool _isModified;
        mutable glm::mat4 _cachedTrans;
    };

}
