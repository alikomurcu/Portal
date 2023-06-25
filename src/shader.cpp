#include "shader.hpp"

/* Private Methods */

bool Shader::ReadDataFromFile (const std::string& fileName, std::string& data)
{
    std::fstream myfile;

    // Open the input 
    myfile.open(fileName.c_str(), std::ios::in);

    if (myfile.is_open())
    {
        std::string curLine;

        while (getline(myfile, curLine))
        {
            data += curLine;
            if (!myfile.eof())
            {
                data += "\n";
            }
        }

        myfile.close();
    }
    else
    {
        return false;
    }

    return true;
}

GLuint Shader::createVS (const std::string& shaderName)
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

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &shader, &length);
    glCompileShader(vs);

    char output[1024] = {0};
    glGetShaderInfoLog(vs, 1024, &length, output);
    printf("VS compile log: %s\n", output);

	return vs;
}

GLuint Shader::createFS (const std::string& shaderName)
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

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &shader, &length);
    glCompileShader(fs);

    char output[1024] = {0};
    glGetShaderInfoLog(fs, 1024, &length, output);
    printf("FS compile log: %s\n", output);

	return fs;
}

/* Public Methods */

Shader::Shader (const std::string& vertShaderName, const std::string& fragShaderName)
{
    program = glCreateProgram();

    GLuint vs = createVS(vertShaderName);
    GLuint fs = createFS(fragShaderName);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    GLint status;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)
    {
        std::cout << "Program link failed" << std::endl;
        exit(-1);
    }
}
