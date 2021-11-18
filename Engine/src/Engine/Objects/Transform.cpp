#include <glm/ext/matrix_transform.hpp>
#include <imgui.h>
#include "Engine/Objects/Transform.h"

namespace Engine {

    Transform::Transform() : _scale(1, 1, 1),
                             _translation(0, 0, 0),
                             _rotation(0, 0, 0),
                             _isModified(false),
                             _cachedTrans(1.f) {}

    void Transform::SetScale(const glm::vec3 &scale) {
        _isModified = true;
        _scale = scale;
    }

    void Transform::SetRotation(const glm::vec3 &rotation) {
        _isModified = true;
        _rotation = rotation;
    }

    void Transform::SetTranslation(const glm::vec3 &translation) {
        _isModified = true;
        _translation = translation;
    }

    glm::mat4 Transform::GetMatrix() const {
        if (!_isModified)
            return _cachedTrans;

        _isModified = false;
        auto t = glm::mat4(1);
        t = glm::translate(t, _translation);
        t = glm::rotate(t, _rotation.x, {1, 0, 0});
        t = glm::rotate(t, _rotation.z, {0, 0, 1});
        t = glm::rotate(t, _rotation.y, {0, 1, 0});

        t = glm::scale(t, _scale);
        _cachedTrans = t;
        return t;
    }

    void Transform::ImGuiRender() {
        _isModified = true;
        ImGui::DragFloat3("Scale", &_scale[0], 0.01f);
        ImGui::DragFloat3("Translation", &_translation[0], 0.3f);
        ImGui::DragFloat3("Rotation", &_rotation[0], 0.003f);
    }
}
