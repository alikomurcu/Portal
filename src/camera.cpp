#include "camera.hpp"

// constructor for camera class
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float roll) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    transform = new Transform();
    transform->Position = position;
    transform->Front = glm::vec3(0.0f, 0.0f, -1.0f);
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
}
// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    transform->Position = glm::vec3(posX, posY, posZ);
    transform->Front = glm::vec3(0.0f, 0.0f, -1.0f);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    Roll = roll;
}


glm::mat4 Camera::GetViewMatrix()
{
    glm::vec3 front;
    front.x = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    front.y = -glm::sin(glm::radians(Pitch));
    front.z = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    transform->Front = glm::normalize(front);
    transform->Front.z = -transform->Front.z;
    // also re-calculate the Right and Up vector

//        transform->Right = glm::normalize(glm::cross(transform->Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    glm::vec3 right;
    right.x = glm::cos(glm::radians(Yaw));
    right.y = 0;
    right.z = -glm::sin(glm::radians(Yaw));
    transform->Right = glm::normalize(right);

    transform->Up    = glm::normalize(glm::cross(transform->Front, transform->Right));
    
    glm::quat qPitch = glm::angleAxis(glm::radians(Pitch), glm::vec3(1, 0, 0));
    glm::quat qYaw = glm::angleAxis(glm::radians(Yaw), glm::vec3(0, 1, 0));
    // glm::quat qRoll = glm::angleAxis(glm::radians(Roll),glm::vec3(0,0,1));

    //For an FPS camera we can omit roll        ROLL IS OMITTED
    glm::quat orientation = qPitch * qYaw;
    orientation = glm::normalize(orientation);

    glm::mat4 rotate = glm::mat4_cast(orientation);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -transform->Position);

    viewMatrix = rotate * translate;
    return viewMatrix;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        transform->Position += transform->Front * velocity;
    if (direction == BACKWARD)
        transform->Position -= transform->Front * velocity;
}


// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    // restrict pitch to 89 degrees
    if (Pitch + yoffset > 89.0f)
        Pitch = 89.0f;
    else if (Pitch + yoffset < -89.0f)
        Pitch = -89.0f;
    else
        Pitch += yoffset;
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::SetYaw(float angle)
{
    Yaw = angle;
}

void Camera::SetPitch(float angle)
{
    Pitch = angle;
}

void Camera::RotatePitch(float rads) // rotate around cams local X axis
{
    glm::quat qPitch = glm::angleAxis(rads, glm::vec3(1, 0, 0));

    transform->Rotation = glm::normalize(qPitch) * transform->Rotation;
    glm::mat4 rotate = glm::mat4_cast(transform->Rotation);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -transform->Position);

    viewMatrix = rotate * translate;
}
void Camera::RotateYaw(float rads) // rotate around cams local X axis
{
    glm::quat qYaw = glm::angleAxis(rads, glm::vec3(0, 1, 0));

    transform->Rotation = glm::normalize(qYaw) * transform->Rotation;
    glm::mat4 rotate = glm::mat4_cast(transform->Rotation);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -transform->Position);

    viewMatrix = rotate * translate;
}

void Camera::RotateRoll(float rads) // rotate around cams local X axis
{
    glm::quat qRoll = glm::angleAxis(rads, glm::vec3(0, 0, 1));

    transform->Rotation = glm::normalize(qRoll) * transform->Rotation;
    glm::mat4 rotate = glm::mat4_cast(transform->Rotation);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -transform->Position);

    viewMatrix = rotate * translate;
}
