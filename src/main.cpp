#include "main.hpp"

void init() 
{
    mainCamera = new Camera(eyePos, eyeUp);
    shaders.push_back(Shader("shaders/vert.glsl", "shaders/frag.glsl"));
    shaders.push_back(Shader("shaders/ground_vert.glsl", "shaders/ground_frag.glsl"));
    shaders.push_back(Shader("shaders/wall_vert.glsl", "shaders/wall_frag.glsl"));

    models.push_back(Model("assets/left_gate.obj"));
    models.push_back(Model("assets/right_gate.obj"));
    models.push_back(Model("assets/box.obj"));
    models.push_back(Model("assets/ground.obj"));
    models.push_back(Model("assets/back_wall.obj"));
    models.push_back(Model("assets/front_wall.obj"));

    models[3].attach_texture("assets/textures/ground.jpg");
    models[4].attach_texture("assets/textures/ground.jpg");
    models[5].attach_texture("assets/textures/ground.jpg");

    skybox = new Skybox();
    skybox->initShader("shaders/skyboxvs.glsl", "shaders/skyboxfs.glsl");
    skybox->shader->set();
    skybox->loadCubemap();

    glEnable(GL_DEPTH_TEST);
}

void render(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1);
        glClearDepth(1.0f);
        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Temporarily here
        modelingMatrix = glm::mat4(1);
//        viewingMatrix = glm::lookAt(eyePos, eyeDir, eyeUp);
        viewingMatrix = mainCamera->GetViewMatrix();

        // Example use
        shaders[0].set();
        models[0].draw();
        models[1].draw();
        models[2].draw();

        modelingMatrix = glm::mat4(1);
        shaders[1].set(models[3].texture_num);
        models[3].draw();

        shaders[2].set(models[4].texture_num);
        models[4].draw();
        models[5].draw();

        // draw skybox as last
        modelingMatrix = glm::rotate<float>(glm::mat4(1.0), -glm::radians(90.), glm::vec3(1.0, 0.0, 0.0)); // Workarounds to fix skybox
        modelingMatrix *= glm::rotate<float>(glm::mat4(1.0), -glm::radians(180.), glm::vec3(0.0, 0.0, 1.0));
        viewingMatrix =  glm::mat4(glm::mat3(viewingMatrix));
        skybox->shader->set();
        skybox->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main(int argc, char** argv)   // Create Main Function For Bringing It All Together
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 640, height = 480;
    window = glfwCreateWindow(width, height, "Simple Example", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    char rendererInfo[512] = {0};
    strcpy(rendererInfo, (const char*) glGetString(GL_RENDERER));
    strcat(rendererInfo, " - ");
    strcat(rendererInfo, (const char*) glGetString(GL_VERSION));
    glfwSetWindowTitle(window, rendererInfo);

    init();

    glfwSetKeyCallback(window, keyboard);
    glfwSetWindowSizeCallback(window, reshape);
    glfwSetCursorPosCallback(window, mouse_callback);

    reshape(window, width, height); // need to call this once ourselves
    render(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
