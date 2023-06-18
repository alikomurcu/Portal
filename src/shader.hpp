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

        bool ReadDataFromFile(const std::string& fileName, std::string& data);
        GLuint createVS(const std::string& shaderName);
        GLuint createFS(const std::string& shaderName);

    public:
        Shader (const std::string& vertShaderName, const std::string& fragShaderName);
        void set (void);
};

#endif // SHADER_HPP