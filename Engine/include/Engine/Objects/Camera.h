#pragma once

namespace Engine {
    class Camera {
    public:
        Camera();
        glm::mat4 GetView() const;
        void MovePosition(glm::vec3 vec);
        void MoveDirection(float yaw, float pitch);
        float RotatingSpeed = 0.07;
        float MovementSpeed = 20;
        void ImGuiRender();
    private:
        glm::vec3 GetDirection() const;
        glm::vec3 _position;
        float _yaw, _pitch;
    };
}