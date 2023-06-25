#include "main.hpp"

void init() 
{
    scene = new Scene();
    mainCamera = new Camera(eyePos, eyeUp);
    scene->shaders.push_back(Shader("shaders/vert.glsl", "shaders/frag.glsl"));
    scene->shaders.push_back(Shader("shaders/ground_vert.glsl", "shaders/ground_frag.glsl"));
    scene->shaders.push_back(Shader("shaders/wall_vert.glsl", "shaders/wall_frag.glsl"));

    scene->models.push_back(Model("assets/box.obj"));
    scene->models.push_back(Model("assets/ground.obj"));
    scene->models.push_back(Model("assets/back_wall.obj"));
    scene->models.push_back(Model("assets/front_wall.obj"));
    scene->models.push_back(Model("assets/left_border.obj"));
    scene->models.push_back(Model("assets/right_border.obj"));

    scene->models[0].attach_shader(&scene->shaders[0]);
    scene->models[1].attach_shader(&scene->shaders[1]);
    scene->models[2].attach_shader(&scene->shaders[2]);
    scene->models[3].attach_shader(&scene->shaders[2]);
    scene->models[4].attach_shader(&scene->shaders[0]);
    scene->models[5].attach_shader(&scene->shaders[0]);

    scene->models[1].attach_texture("assets/textures/ground.jpg");
    scene->models[2].attach_texture("assets/textures/ground.jpg");
    scene->models[3].attach_texture("assets/textures/ground.jpg");

    Skybox *skybox = new Skybox();
    skybox->initShader("shaders/skyboxvs.glsl", "shaders/skyboxfs.glsl");
    skybox->shader->use();
    skybox->loadCubemap();
    scene->skybox = skybox;

    Shader *portalShader = new Shader("shaders/portal_vert.glsl", "shaders/portal_frag.glsl");
    portal1 = new Portal();
    portal2 = new Portal();
    portal1->attach_shader(portalShader);
    portal2->attach_shader(portalShader);
    portal1->setDestination(portal2);
    portal2->setDestination(portal1);
    portal1->set_position(glm::vec3(-3.11356f, 1.4f, -1.95163f));
    portal2->set_position(glm::vec3(3.11356f, 1.4f, -1.95163f));
    portal1->set_orientation(glm::vec3(0.0f, 1.0f, 0.0f), M_PI/3.0f, true);
    portal2->set_orientation(glm::vec3(0.0f, 1.0f, 0.0f), -M_PI/3.0f, true);

    scene->portals.push_back(portal1);
    scene->portals.push_back(portal2);
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

        mainCamera->ProcessMovement();
        
        // Temporarily here
        modelingMatrix = glm::mat4(1);
//        viewingMatrix = glm::lookAt(eyePos, eyeDir, eyeUp);
        viewingMatrix = mainCamera->GetViewMatrix();


        scene->recursiveDraw(viewingMatrix, projectionMatrix, 0, 1);

        // Example use
//        scene->models[0].draw();
//        scene->models[1].draw();
//        scene->models[2].draw();
//
//        scene->models[3].draw();
//
//
//        portal1->shader->use();
//        portal1->shader->setMat4("projectionMatrix", projectionMatrix);
//        portal1->shader->setMat4("viewingMatrix", viewingMatrix);
//        portal1->shader->setMat4("modelingMatrix", portal1->modelMat);
//        portal1->draw();
//        portal2->shader->setMat4("modelingMatrix", portal2->modelMat);
//        portal2->draw();

//        scene->recursiveDraw(viewingMatrix, projectionMatrix, 0, 1);
        // draw skybox as last
//        viewingMatrix =  glm::mat4(glm::mat3(viewingMatrix));
//        skybox->shader->use();
//        skybox->shader->setMat4("projectionMatrix", projectionMatrix);
//        skybox->shader->setMat4("viewingMatrix", viewingMatrix);
//        skybox->draw();

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
