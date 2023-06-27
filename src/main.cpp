#include "main.hpp"

void init() 
{
    scene = new Scene();
    mainCamera = new Camera(eyePos, eyeUp);
    scene->shaders.push_back(Shader("shaders/vert.glsl", "shaders/frag.glsl"));
    scene->shaders.push_back(Shader("shaders/ground_vert.glsl", "shaders/ground_frag.glsl"));
    scene->shaders.push_back(Shader("shaders/wall_vert.glsl", "shaders/wall_frag.glsl"));
    scene->shaders.push_back(Shader("shaders/border_vert.glsl", "shaders/border_frag.glsl"));

    scene->models.push_back(Model("assets/box.obj")); // Use 0th slot for the moving object
    scene->models.push_back(Model("assets/ground.obj"));
    scene->models.push_back(Model("assets/back_wall.obj"));
    scene->models.push_back(Model("assets/front_wall.obj"));
    scene->models.push_back(Model("assets/border.obj"));
    scene->models.push_back(Model("assets/border.obj"));

    scene->models[0].attach_shader(&scene->shaders[0]);
    scene->models[1].attach_shader(&scene->shaders[1]);
    scene->models[2].attach_shader(&scene->shaders[2]);
    scene->models[3].attach_shader(&scene->shaders[2]);
    scene->models[4].attach_shader(&scene->shaders[3]);
    scene->models[5].attach_shader(&scene->shaders[3]);

    scene->models[4].set_position(scene->models[5].position + glm::vec3(0.0f, 0.0f, 10.5f));
    scene->models[5].set_position(scene->models[6].position + glm::vec3(0.0f, 0.0f, 10.5f));

    scene->models[1].attach_texture("assets/textures/ground.jpg");
    scene->models[2].attach_texture("assets/textures/ground.jpg");
    scene->models[3].attach_texture("assets/textures/ground.jpg");

    scene->models[0].set_position(glm::vec3(0.0f, 1.0f, -3.0f));

    Skybox *skybox = new Skybox();
    skybox->initShader("shaders/skyboxvs.glsl", "shaders/skyboxfs.glsl");
    skybox->shader->use();
    skybox->loadCubemap();
    scene->skybox = skybox;

    BoxModel *box = new BoxModel();
    box->attach_texture("assets/textures/crate.jpg");
    scene->box = box;

    Shader *portalShader = new Shader("shaders/portal_vert.glsl", "shaders/portal_frag.glsl");
    portal1 = new Portal();
    portal2 = new Portal();

    portal1->attach_shader(portalShader);
    portal2->attach_shader(portalShader);
    portal1->setDestination(portal2);
    portal2->setDestination(portal1);
    portal1->set_position(glm::vec3(-2.0f, 1.5f, 0.0f));
    portal2->set_position(glm::vec3(2.0f, 1.5f, 0.0f));
    portal1->angle = glm::radians(90.f);
    portal2->angle = glm::radians(-90.f);
    portal1->set_orientation(glm::vec3(0.0f, 1.0f, 0.0f), portal1->angle, true);
    portal2->set_orientation(glm::vec3(0.0f, 1.0f, 0.0f), portal2->angle, true);

    portal1->normal = glm::inverse(glm::transpose(glm::mat3(portal1->modelMat))) * glm::vec3(0, 0, 1);
    portal2->normal = glm::inverse(glm::transpose(glm::mat3(portal2->modelMat))) * glm::vec3(0, 0, 1);

    scene->portals.push_back(portal1);
    scene->portals.push_back(portal2);

    scene->models[4].modelMat = portal1->modelMat;
    scene->models[5].modelMat = portal2->modelMat;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void collisionHandler (Portal *portal)
{
    float collision = glm::dot((mainCamera->transform->Position - portal->position), (portal->normal)); // Plane equation
    //float behind_control = glm::dot(portal->normal, mainCamera->transform->Front);

    glm::vec2 temp1 = glm::vec2(mainCamera->transform->Position.x, mainCamera->transform->Position.z);
    glm::vec2 temp2 = glm::vec2(portal->position.x, portal->position.z);
    float dist = glm::distance(temp1, temp2); // Point distance

    if (dist < PORTAL_WIDTH / 2.0 && abs(collision) < 0.1)
    {
        std::cout << "Teleported!!!" << std::endl;
        mainCamera->transform->Position.y -= 0.5;
        mainCamera->transform->Position += portal->destination->position - portal->position;
        mainCamera->transform->Position.y += 0.5;
        mainCamera->transform->Position.x += 0.25 * portal->destination->normal.x;
        mainCamera->transform->Position.z += 0.25 * portal->destination->normal.z;

        //mainCamera->Yaw += glm::degrees(portal->destination->angle) - glm::degrees(portal->angle);

        float d_product = glm::dot(-portal->normal, portal->destination->normal);
        float dist_mult = glm::length(-portal->normal) * glm::length(portal->destination->normal);
        float angle = acos(d_product / dist_mult);
        
        //mainCamera->Yaw += glm::degrees(angle);
    }

    collision = glm::dot((scene->models[0].position - portal->position), (portal->normal));
    temp1 = glm::vec2(scene->models[0].position.x, scene->models[0].position.z);
    temp2 = glm::vec2(portal->position.x, portal->position.z);
    dist = glm::distance(temp1, temp2);

    if (dist < PORTAL_WIDTH / 2.0 && abs(collision) < 0.1)
    {
        std::cout << "Teleported!!!" << std::endl;
        scene->models[0].position.y -= 0.5;
        scene->models[0].position += portal->destination->position - portal->position;
        scene->models[0].position.y += 0.5;
        scene->models[0].position.x += 0.25 * portal->destination->normal.x;
        scene->models[0].position.z += 0.25 * portal->destination->normal.z;

        //mainCamera->Yaw += glm::degrees(portal->destination->angle) - glm::degrees(portal->angle);

        float d_product = glm::dot(-portal->normal, portal->destination->normal);
        float dist_mult = glm::length(-portal->normal) * glm::length(portal->destination->normal);
        float angle = acos(d_product / dist_mult);
        
        //mainCamera->Yaw += glm::degrees(angle);
    }

    collision = glm::dot((scene->box->position - portal->position), (portal->normal));
    temp1 = glm::vec2(scene->box->position.x, scene->box->position.z);
    temp2 = glm::vec2(portal->position.x, portal->position.z);
    dist = glm::distance(temp1, temp2);

    if (dist < PORTAL_WIDTH / 2.0 && abs(collision) < 0.01)
    {
        std::cout << "Teleported!!!" << std::endl;
        scene->box->position.y -= 0.5;
        scene->box->position += portal->destination->position - portal->position;
        scene->box->position.y += 0.5;
        //scene->box->position.x += 0.25 * portal->destination->normal.x;
        //scene->box->position.z += 0.25 * portal->destination->normal.z;

        //mainCamera->Yaw += glm::degrees(portal->destination->angle) - glm::degrees(portal->angle);

        float d_product = glm::dot(-portal->normal, portal->destination->normal);
        float dist_mult = glm::length(-portal->normal) * glm::length(portal->destination->normal);
        float angle = acos(d_product / dist_mult);
        
        //mainCamera->Yaw += glm::degrees(angle);
    }
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

        collisionHandler(portal1);
        collisionHandler(portal2);

        //scene->models[0].position.x += 0.01; // Box without geometry shader
        //scene->models[0].set_position(scene->models[0].position);

        scene->box->position.x += 0.01; // Box with geometry shader
        scene->box->set_position(scene->box->position);

        //std::cout << mainCamera->transform->Position.x << " " <<  mainCamera->transform->Position.y << " " << mainCamera->transform->Position.z << std::endl;
        viewingMatrix = mainCamera->GetViewMatrix();

        scene->recursiveDraw(viewingMatrix, projectionMatrix, 5, 0);

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
