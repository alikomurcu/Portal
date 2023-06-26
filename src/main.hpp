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

#endif // MAIN_HPP