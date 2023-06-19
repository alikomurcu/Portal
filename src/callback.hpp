#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include "common.hpp"
#include "camera.hpp"

void reshape(GLFWwindow* window, int w, int h);

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);


// mouse positions for camera
inline bool firstMouse = true;
inline float lastX = (float)gWidth / 2.0;
inline float lastY = (float)gHeight / 2.0;

// Camera related vairables
inline Camera *mainCamera;

inline bool toggleCursor = true;
#endif // CALLBACK_HPP