#ifndef MAIN_HPP
#define MAIN_HPP

#include "callback.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "transform.hpp"
#include "common.hpp"
#include "skybox.hpp"
#include "scene.hpp"

// stb related
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

inline Scene *scene;

inline Skybox* skybox;

inline Portal *portal1, *portal2;

glm::vec3 portal1Pos(-2.0f, 1.5f, 0.5f);
glm::vec3 portal2Pos(2.0f, 1.5f, 0.5f);

float portal1Angle = glm::radians(90.f);
float portal2Angle = glm::radians(-90.f);

#endif // MAIN_HPP