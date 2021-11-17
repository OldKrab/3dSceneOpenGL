#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui.h>
#include "Engine/Objects/Camera.h"

namespace Engine {

    Camera::Camera() :
            _yaw(-90), _pitch(0), _position(0, 0, 0) {

    }

    glm::mat4 Camera::GetView() const {
        glm::mat4 view;
        auto t = GetDirection();
        view = glm::lookAt(_position,
                           GetDirection() + _position,
                           {0, 1, 0});
        return view;
    }

    void Camera::MovePosition(glm::vec3 vec) {
        vec *= MovementSpeed;
        auto right = glm::normalize(glm::cross(GetDirection(), {0, 1, 0}));
        auto front = glm::normalize(glm::cross(right, {0, -1, 0}));
        _position += right * vec.x;
        _position += glm::vec3{0, 1, 0} * vec.y;
        _position += front * vec.z;
    }

    void Camera::MoveDirection(float yaw, float pitch) {
        _yaw += yaw * RotatingSpeed;
        _pitch += pitch * RotatingSpeed;
    }

    glm::vec3 Camera::GetDirection() const {
        return {
                std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch)),
                std::sin(glm::radians(_pitch)),
                std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch))
        };
    }

    void Camera::ImGuiRender() {
        if (ImGui::CollapsingHeader("Camera")) {
            ImGui::Indent();
            float zero = 0;
            ImGui::DragFloat("Movement Speed", &MovementSpeed, 0.05, zero, 100);
            ImGui::DragFloat("Rotating Speed", &RotatingSpeed, 0.0001, zero, 0.3f);
            ImGui::Unindent();
        }

    }
}