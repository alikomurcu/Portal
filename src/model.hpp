#ifndef MODEL_HPP
#define MODEL_HPP

#include "common.hpp"
#include "stb_image.h"
#include "shader.hpp"

struct Vertex
{
    Vertex(GLfloat inX, GLfloat inY, GLfloat inZ) : x(inX), y(inY), z(inZ) { }
    GLfloat x, y, z;
};

struct Texture
{
    Texture(GLfloat inU, GLfloat inV) : u(inU), v(inV) { }
    GLfloat u, v;
};

struct Normal
{
    Normal(GLfloat inX, GLfloat inY, GLfloat inZ) : x(inX), y(inY), z(inZ) { }
    GLfloat x, y, z;
};

struct Face
{
    Face(int v[], int t[], int n[]) {
        vIndex[0] = v[0];
        vIndex[1] = v[1];
        vIndex[2] = v[2];
        tIndex[0] = t[0];
        tIndex[1] = t[1];
        tIndex[2] = t[2];
        nIndex[0] = n[0];
        nIndex[1] = n[1];
        nIndex[2] = n[2];
    }
    GLuint vIndex[3], tIndex[3], nIndex[3];
};

class Model
{
    private:
        GLuint vao;
        GLuint vertexBuffer;
        GLuint indexBuffer;
        GLuint faceCount;
        GLuint texture;
        inline static std::vector<Vertex> gVertices;
        inline static std::vector<Texture> gTextures;
        inline static std::vector<Normal> gNormals;
        inline static std::vector<Face> gFaces;
        inline static int texture_ctr = 0;
        bool ParseObj(const std::string& fileName);
    public:
        Shader* shader;
        int texture_num;
        glm::mat4 modelMat = glm::mat4(1), viewMat;
        glm::quat orientation;
        glm::vec3 position, scale;
        Model (const std::string &fileName, glm::vec3 position=glm::vec3(0,0,0));
        Model();
        virtual void draw (glm::mat4 viewingMatrix, glm::mat4 projectionMatrix);
        void attach_texture (const std::string &fileName);
        void attach_shader (Shader * s);
        void set_scale(glm::vec3 scale);
        void set_position (glm::vec3 position);
        void set_orientation (glm::quat orientation);
        void set_orientation(glm::vec3 const &axis, float radAngle, bool worldSpace);
        void update_modelMat();
};

#endif // MODEL_HPP