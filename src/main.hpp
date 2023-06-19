#ifndef MAIN_HPP
#define MAIN_HPP

#include "callback.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "transform.hpp"
#include "common.hpp"
#include "skybox.hpp"

// stb related
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<Shader> shaders;

std::vector<Model> models;


inline Skybox* skybox;

#endif // MAIN_HPP