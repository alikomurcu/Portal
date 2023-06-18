#ifndef COMMON_HPP
#define COMMON_HPP

// Standard libraries
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

// OpenGL related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

inline int gWidth, gHeight;

inline glm::mat4 projectionMatrix;
inline glm::mat4 viewingMatrix;
inline glm::mat4 modelingMatrix;

inline std::vector<GLuint> programs;

#endif // COMMON_HPP