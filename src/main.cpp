#include "main.hpp"

void init() 
{
    scene = new Scene();
    mainCamera = new Camera(eyePos, eyeUp);
    scene->shaders.push_back(Shader("shaders/vert.glsl", "shaders/frag.glsl"));
    scene->shaders.push_back(Shader("shaders/ground_vert.glsl", "shaders/ground_frag.glsl"));
    scene->shaders.push_back(Shader("shaders/wall_vert.glsl", "shaders/wall_frag.glsl"));

    scene->models.emplace_back("assets/left_gate.obj");
    scene->models.push_back(Model("assets/right_gate.obj"));
    scene->models.push_back(Model("assets/box.obj"));
    scene->models.push_back(Model("assets/ground.obj"));
    scene->models.push_back(Model("assets/back_wall.obj"));
    scene->models.push_back(Model("assets/front_wall.obj"));

    scene->models[0].attach_shader(&scene->shaders[0]);
    scene->models[1].attach_shader(&scene->shaders[0]);
    scene->models[2].attach_shader(&scene->shaders[0]);
    scene->models[3].attach_shader(&scene->shaders[1]);
    scene->models[4].attach_shader(&scene->shaders[2]);
    scene->models[5].attach_shader(&scene->shaders[2]);

    scene->models[3].attach_texture("assets/textures/ground.jpg");
    scene->models[4].attach_texture("assets/textures/ground.jpg");
    scene->models[5].attach_texture("assets/textures/ground.jpg");

    skybox = new Skybox();
    skybox->initShader("shaders/skyboxvs.glsl", "shaders/skyboxfs.glsl");
    skybox->shader->use();
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

        scene->shaders[0].setMat4("projectionMatrix", projectionMatrix);
        scene->shaders[1].setMat4("projectionMatrix", projectionMatrix);
        scene->shaders[2].setMat4("projectionMatrix", projectionMatrix);
        scene->shaders[0].setMat4("viewingMatrix", viewingMatrix);
        scene->shaders[1].setMat4("viewingMatrix", viewingMatrix);
        scene->shaders[2].setMat4("viewingMatrix", viewingMatrix);

        // Example use
        scene->models[0].draw();
        scene->models[1].draw();
        scene->models[2].draw();

        modelingMatrix = glm::mat4(1);
        scene->models[3].draw();

        scene->models[4].draw();
        scene->models[5].draw();

        // draw skybox as last
        viewingMatrix =  glm::mat4(glm::mat3(viewingMatrix));
        skybox->shader->setMat4("projectionMatrix", projectionMatrix);
        skybox->shader->setMat4("viewingMatrix", viewingMatrix);
        skybox->shader->use();
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
