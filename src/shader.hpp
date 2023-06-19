#ifndef SHADER_HPP
#define SHADER_HPP

#include "common.hpp"

class Shader
{
    private:
        GLuint program;

        GLint modelingMatrixLoc;
        GLint viewingMatrixLoc;
        GLint projectionMatrixLoc;
        GLint eyePosLoc;
        GLint texLoc;

        bool ReadDataFromFile(const std::string& fileName, std::string& data);
        GLuint createVS(const std::string& shaderName);
        GLuint createFS(const std::string& shaderName);

    public:
        Shader (const std::string& vertShaderName, const std::string& fragShaderName);
        void set (void);
        void set (int texture_id);
};

#endif // SHADER_HPP