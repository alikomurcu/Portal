#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "common.hpp"
#include "transform.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         =  0.0f;
const float PITCH       =  0.0f;
const float ROLL        =  0.0f;
const float SPEED       =  0.1f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  90.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    Transform* transform;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    float Roll;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    glm::mat4 viewMatrix;
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float roll = ROLL);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll);
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessMovement(void);
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset);
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);
    void SetYaw(float angle);
    void SetPitch(float angle);
    void RotatePitch(float rads); // rotate around cams local X axis
    void RotateYaw(float rads); // rotate around cams local X axis
    void RotateRoll(float rads); // rotate around cams local X axis

    bool forwardMovement;
    bool backwardMovement;
    bool leftMovement;
    bool rightMovement;
};
#endif  // CAMERA_HPP
