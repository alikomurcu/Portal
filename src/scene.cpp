#include "scene.hpp"

Scene::Scene()
{
};

void Scene::drawOtherObjects(glm::mat4 viewMat, glm::mat4 projMat)
{
    for (auto &model : models)
    {
        model.draw(viewMat, projMat);
    }

    glm::mat4 viewing =  glm::mat4(glm::mat3(viewMat));
    skybox->shader->use();
    skybox->shader->setMat4("projectionMatrix", projMat);
    skybox->shader->setMat4("viewingMatrix", viewing);
    skybox->draw();

    box->draw(viewMat, projMat);
}

void Scene::recursiveDraw(glm::mat4 const &viewMat, glm::mat4 const &projMat, size_t maxRecursionLevel, size_t recursionLevel)
{
    for (auto &portal : portals)
    {
        // Disable color and depth writing
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);

        // Disable depth test
        glDisable(GL_DEPTH_TEST);

        // Enable stencil test, not to draw
        // outside of current portal depth
        glEnable(GL_STENCIL_TEST);

        // Fail stencil test when inside of outer portal
        // (fail where we should be drawing the inner portal)
        glStencilFunc(GL_NOTEQUAL, recursionLevel, 0xFF);

        // Increment stencil value on stencil fail
        // (on area of inner portal)
        glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);

        // Enable (writing into) all stencil bits
        glStencilMask(0xFF);

        // Draw portal into stencil buffer
        portal->draw(viewMat, projMat);


        // Calculate viewing matrix of virtual camera
        glm::mat4 destinationView =
                               viewMat * portal->modelMat
                             * glm::rotate(glm::mat4(1.0f), glm::radians(180.f), glm::vec3(0.0f, 1.0f, 0.0f) * portal->orientation)
                             * glm::inverse(portal->destination->modelMat);

        // Base case, render inside of inner portal
        if (recursionLevel == maxRecursionLevel)
        {
            // Enable color and depth drawing
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            glDepthMask(GL_TRUE);

            // Clear the depth buffer so we don't interfere with stuff
            // outside of this inner portal
            glClear(GL_DEPTH_BUFFER_BIT);

            // Enable the depth test
            // So the stuff we render here is rendered correctly
            glEnable(GL_DEPTH_TEST);

            // Enable stencil test
            // So we can limit drawing inside of the inner portal
            glEnable(GL_STENCIL_TEST);

            // Disable drawing into stencil buffer
            glStencilMask(0x00);

            // Draw only where stencil value == recursionLevel + 1
            // which is where we just drew the new portal
            glStencilFunc(GL_EQUAL, recursionLevel + 1, 0xFF);

            // Draw scene objects with destinationView, limited to stencil buffer
            // use an edited projection matrix to set the near plane to the portal plane
            drawOtherObjects(destinationView, portal->obliqueClippingOnProjMat(destinationView, projMat));
            //drawOtherObjects(destinationView, projMat);
        }
        else
        {
            // Recursion case
            // Pass our new view matrix and the clipped projection matrix (see above)
            recursiveDraw(destinationView, portal->obliqueClippingOnProjMat(destinationView, projMat), maxRecursionLevel, recursionLevel + 1);
        }

        // Disable color and depth drawing
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);

        // Enable stencil test and stencil drawing
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0xFF);

        // Fail stencil test when inside of our newly rendered
        // inner portal
        glStencilFunc(GL_NOTEQUAL, recursionLevel + 1, 0xFF);

        // Decrement stencil value on stencil fail
        // This resets the incremented values to what they were before,
        // eventually ending up with a stencil buffer full of zero's again
        // after the last (outer) step.
        glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);

        // Draw portal into stencil buffer
        portal->draw(viewMat, projMat);
    }

    // Disable the stencil test and stencil writing
    glDisable(GL_STENCIL_TEST);
    glStencilMask(0x00);

    // Disable color writing
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    // Enable the depth test, and depth writing.
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Make sure we always write the data into the buffer
    glDepthFunc(GL_ALWAYS);

    // Clear the depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Draw portals into depth buffer
    for (auto &portal : portals)
        portal->draw(viewMat, projMat);

    // Reset the depth function to the default
    glDepthFunc(GL_LESS);

    // Enable stencil test and disable writing to stencil buffer
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0x00);

    // Draw at stencil >= recursionlevel
    // which is at the current level or higher (more to the inside)
    // This basically prevents drawing on the outside of this level.
    glStencilFunc(GL_LEQUAL, recursionLevel, 0xFF);

    // Enable color and depth drawing again
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);

    // And enable the depth test
    glEnable(GL_DEPTH_TEST);

    // Draw scene objects normally, only at recursionLevel
    drawOtherObjects(viewMat, projMat);
}
