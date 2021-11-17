#include <glm/ext/matrix_transform.hpp>
#include "Engine/Objects/Transformable.h"

namespace Engine {

    Transformable::Transformable() : _scale(1, 1, 1),
                                     _translation(0, 0, 0),
                                     _rotation(0, 0, 0),
                                     _isModified(false),
                                     _cachedTrans(1.f) {}

    void Transformable::SetScale(const glm::vec3 &scale) {
        _isModified = true;
        _scale = scale;
    }

    void Transformable::SetRotation(const glm::vec3 &rotation) {
        _isModified = true;
        _rotation = rotation;
    }

    void Transformable::SetTranslation(const glm::vec3 &translation) {
        _isModified = true;
        _translation = translation;
    }

    glm::mat4 Transformable::GetTransform() const {
        if(!_isModified)
            return _cachedTrans;

        _isModified = false;
        auto t = glm::mat4(1);
        t = glm::translate(t, _translation);
        t = glm::rotate(t, _rotation.x, {1, 0, 0});
        t = glm::rotate(t, _rotation.y, {0, 1, 0});
        t = glm::rotate(t, _rotation.z, {0, 0, 1});
        t = glm::scale(t, _scale);
        _cachedTrans = t;
        return t;
    }
}
