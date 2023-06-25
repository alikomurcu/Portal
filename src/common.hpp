#ifndef COMMON_HPP
#define COMMON_HPP

// Standard libraries
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>

// OpenGL related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>
// Macros
#define BUFFER_OFFSET(i) ((char*)NULL + (i))

// Settings
#include "settings.hpp"

// Global variables
inline int gWidth, gHeight;

inline glm::mat4 projectionMatrix;
inline glm::mat4 viewingMatrix;
inline glm::mat4 modelingMatrix;

inline std::vector<GLuint> programs;

// Camera in the origin, looking to -z and +y is up.
inline glm::vec3 eyePos(0., 2., 4.);
inline glm::vec3 eyeDir(0., 1., 0.);
inline glm::vec3 eyeUp(0., 0., 1.);

#endif // COMMON_HPP