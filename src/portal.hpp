#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "common.hpp"
#include "shader.hpp"
#include "model.hpp"

class Portal: public Model
{
public:
    Portal* destination;
    Portal();
    glm::mat4 const clippedProjMat(glm::mat4 const &destView, glm::mat4 const &projMat) const;
    void setDestination(Portal* dest);
    Portal* getDestination() const;
};



#endif // PORTAL_HPP