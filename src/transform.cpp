#include "transform.hpp"

Transform::Transform() {
    Position = glm::vec3(-0.1f, -0.2f, -7.0f);
    Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    Rotation = glm::quat (glm::vec3(0.0f, 0.0f, 0.0f));
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    Right = glm::vec3(1.0f, 0.0f, 0.0f);
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
}