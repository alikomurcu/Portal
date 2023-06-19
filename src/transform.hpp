#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "common.hpp"

// This is a class for handling transformations
class Transform {
private:
    glm::mat4 matT, matR, matS;
public:
    // Transform attributes
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::quat Rotation;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;

    Transform();
};
#endif // TRANSFORM_HPP
