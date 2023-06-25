#ifndef SCENE_HPP
#define SCENE_HPP
#include "common.hpp"
#include "model.hpp"
#include "portal.hpp"
#include "skybox.hpp"

class Scene
{
public:
    std::vector<Model> models;
    std::vector<Portal*> portals;
    std::vector<Shader> shaders;

    Scene();
    Skybox *skybox;
    void recursiveDraw(glm::mat4 const &viewMat, glm::mat4 const &projMat, size_t maxRecursionLevel, size_t recursionLevel);
    void drawNonPortals(glm::mat4 viewMat, glm::mat4 projMat);
};

#endif // SCENE_HPP