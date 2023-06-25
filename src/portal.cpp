#include "common.hpp"
#include "portal.hpp"

Portal::Portal() : Model()
{
    // portal VAO
    glGenVertexArrays(1, &portalVAO);
    glGenBuffers(1, &portalVBO);
    glBindVertexArray(portalVAO);
    glBindBuffer(GL_ARRAY_BUFFER, portalVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(portalVertices), &portalVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    destination = nullptr;
    orientation = glm::quat {1.0f, 0.0f, 0.0f, 0.0f};
}

void Portal::draw(glm::mat4 viewMat, glm::mat4 projMat)
{
    shader->use();
    shader->setMat4("projectionMatrix", projMat);
    shader->setMat4("viewingMatrix", viewMat);
    shader->setMat4("modelingMatrix", modelMat);
    // skybox cube
    glBindVertexArray(portalVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Portal::setDestination(Portal *dest)
{
    destination = dest;
}

Portal *Portal::getDestination() const
{
    return destination;
}


glm::mat4 const Portal::clippedProjMat(glm::mat4 const &viewMat, glm::mat4 const &projMat) const
{
    float dist = glm::length(position);
    glm::vec4 clipPlane(orientation * glm::vec3(0.0f, 0.0f, -1.0f), dist);
    clipPlane = glm::inverse(glm::transpose(viewMat)) * clipPlane;

    if (clipPlane.w > 0.0f)
        return projMat;

    glm::vec4 q = glm::inverse(projMat) * glm::vec4(
            glm::sign(clipPlane.x),
            glm::sign(clipPlane.y),
            1.0f,
            1.0f
    );

    glm::vec4 c = clipPlane * (2.0f / (glm::dot(clipPlane, q)));

    glm::mat4 newProj = projMat;
    // third row = clip plane - fourth row
    newProj = glm::row(newProj, 2, c - glm::row(newProj, 3));

    return newProj;
}
