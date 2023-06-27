#include "box.hpp"


BoxModel::BoxModel() : shader(BoxShader("shaders/box_vert.glsl", "shaders/box_frag.glsl", "shaders/box_geom.glsl"))
{
    glGenVertexArrays(1, &boxVAO);
    glGenBuffers(1, &boxVBO);
    glBindVertexArray(boxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), &boxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}
    
void BoxModel::draw(glm::mat4 viewingMat, glm::mat4 projectionMat)
{
    shader.use();
    shader.setMat4("modelingMatrix", modelMat);
	shader.setMat4("viewingMatrix", viewingMat);
	shader.setMat4("projectionMatrix", projectionMat);

    glBindVertexArray(boxVAO);

    shader.setInt("tex", 10);
	glActiveTexture(GL_TEXTURE0 + 10);
	glBindTexture(GL_TEXTURE_2D, texture);

    glDrawArrays(GL_POINTS, 0, 8); 
}

GLuint BoxShader::createGS(const std::string& shaderName)
{
    std::string shaderSource;

    std::string filename(shaderName);
    if (!ReadDataFromFile(filename, shaderSource))
    {
        std::cout << "Cannot find file name: " + filename << std::endl;
        exit(-1);
    }

    GLint length = shaderSource.length();
    const GLchar* shader = (const GLchar*) shaderSource.c_str();

    GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gs, 1, &shader, &length);
    glCompileShader(gs);

    char output[1024] = {0};
    glGetShaderInfoLog(gs, 1024, &length, output);
    printf("GS compile log: %s\n", output);

	return gs;
}

BoxShader::BoxShader(const std::string& vertShaderName, const std::string& fragShaderName, const std::string& geomShaderName)
{
    program = glCreateProgram();

    GLuint vs = createVS(vertShaderName);
    GLuint fs = createFS(fragShaderName);
    GLuint gs = createGS(geomShaderName);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glAttachShader(program, gs);

    GLint status;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)
    {
        std::cout << "Program link failed" << std::endl;
        exit(-1);
    }
}

// A simplified position/modelMatrix update
void BoxModel::set_position(glm::vec3 position) {
    this->position = position;
    update_modelMat();
}

void BoxModel::update_modelMat()
{
    modelMat = glm::translate(glm::mat4(1.0f), position);
}

void BoxModel::attach_texture (const std::string &fileName)
{
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + 10); //Hardcoded to use texture 10
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width, height, nrChannels;
	unsigned char *data;

	data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}