#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "common.hpp"
#include "shader.hpp"
#include "model.hpp"

class Portal: public Model
{
public:
    Portal();
    Portal* destination;
    glm::mat4 const clippedProjMat(glm::mat4 const &destView, glm::mat4 const &projMat) const;
    void setDestination(Portal* dest);
};



#endif // PORTAL_HPP