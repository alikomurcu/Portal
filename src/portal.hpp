#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "common.hpp"
#include "shader.hpp"
#include "model.hpp"

inline float portalVertices[] = {
        -1.0f, -1.4f, 0.0f,
        1.0f, -1.4f, 0.0f,
        1.0f, 1.4f, 0.0f,

        1.0f, 1.4f, 0.0f,
        -1.0f,  1.4f, 0.0f,
        -1.0f, -1.4f, 0.0f,
};

class Portal: public Model
{
protected:
    unsigned int portalVAO, portalVBO;
public:
    float angle;
    glm::vec3 normal = glm::vec3(0, 0, 1);
    Portal* destination;
    Portal();
    glm::mat4 const obliqueClippingOnProjMat(glm::mat4 const &destView, glm::mat4 const &projMat) const;
    void setDestination(Portal *dest);
    Portal* getDestination() const;
    void draw(glm::mat4 viewMat, glm::mat4 projMat);
};



#endif // PORTAL_HPP