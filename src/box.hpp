#ifndef BOX_HPP
#define BOX_HPP

#include "common.hpp"
#include "shader.hpp"
#include "model.hpp"

inline float boxVertices[] = {
        0.5f, 1.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        0.0f, 1.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 1.0f, 0.5f,
        0.0f, 1.0f, -0.5f,
};

class BoxShader: public Shader
{
    protected:
        GLuint createGS(const std::string& shaderName);

    public:
        BoxShader(const std::string& vertShaderName, const std::string& fragShaderName, const std::string& geomShaderName);
};

class BoxModel
{
    protected:
        unsigned int boxVAO, boxVBO;
        BoxShader shader;
        glm::mat4 modelMat = glm::mat4(1);
        GLuint texture;

    public:
        glm::vec3 position = glm::vec3(0, 0, 0);
        BoxModel();
        void draw(glm::mat4 viewingMat, glm::mat4 projectionMat);
        void set_position (glm::vec3 position);
        void update_modelMat();
        void attach_texture (const std::string &fileName);
};

#endif // PORTAL_HPP