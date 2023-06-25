#ifndef SCENE_HPP
#define SCENE_HPP
#include "common.hpp"
#include "model.hpp"
#include "portal.hpp"

class Scene
{
public:
    std::vector<Model> models;
    std::vector<Portal> portals;
    std::vector<Shader> shaders;

    Scene();
    void recursiveDraw(glm::mat4 const &viewMat, glm::mat4 const &projMat, int recursionLevel, int maxRecursionLevel);
    void drawNonPortals(glm::mat4 viewMat, glm::mat4 projMat);
};

#endif // SCENE_HPP