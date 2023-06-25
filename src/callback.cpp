#include "callback.hpp"


void reshape(GLFWwindow* window, int w, int h)
{
    w = w < 1 ? 1 : w;
    h = h < 1 ? 1 : h;

    gWidth = w;
    gHeight = h;

    glViewport(0, 0, w, h);

	float fovyRad = (float) (45.0 / 180.0) * M_PI;

    projectionMatrix = glm::perspective(fovyRad, gWidth/(float) gHeight, 0.1f, 100.0f);
	viewingMatrix = glm::mat4(1);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)       // TODO: speedup logic
    {
        mainCamera->forwardMovement = true;
        // mainCamera->transform->Position += mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        mainCamera->backwardMovement = true;
        // mainCamera->transform->Position -= mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        mainCamera->leftMovement = true;
        // mainCamera->transform->Position -= mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        mainCamera->rightMovement = true;
        // mainCamera->transform->Position -= mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)       // TODO: speedup logic
    {
        mainCamera->forwardMovement = false;
        // mainCamera->transform->Position += mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        mainCamera->backwardMovement = false;
        // mainCamera->transform->Position -= mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        mainCamera->leftMovement = false;
        // mainCamera->transform->Position -= mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        mainCamera->rightMovement = false;
        // mainCamera->transform->Position -= mainCamera->transform->Front * 0.1f;
    }
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        //glShadeModel(GL_SMOOTH);
        //activeProgramIndex = 0;
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        //glShadeModel(GL_SMOOTH);
        //activeProgramIndex = 1;
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        //glShadeModel(GL_FLAT);
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        if (toggleCursor)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        toggleCursor = !toggleCursor;
    }


}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    if(INVERT_MOUSE_X) xoffset *= -1;
    if(INVERT_MOUSE_Y) yoffset *= -1;
    mainCamera->ProcessMouseMovement(xoffset, yoffset);
}