#include <fstream>
#include <iostream>

#include "shader.hh"
#include "exceptions.hh"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
    for (GLuint shader: shaders_)
    {
        glDeleteShader(shader);
    }
}

GLuint ShaderManager::fromfile(const char* file, GLenum shaderType)
{
    std::ifstream in{file};

    if (in.good())
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();

        return fromstring(contents.c_str(), shaderType);
    }
    throw ShaderException();
}

GLuint ShaderManager::fromstring(const char* program, GLenum shaderType)
{
    // Compile shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &program, NULL);
    glCompileShader(shader);

    // Check compilation status
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        // Display error message
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cerr << "Error while compiling shader" << std::endl;
        std::cerr << buffer << std::endl;
        throw ShaderException();
    }

    // Add id to shader list
    shaders_.emplace_back(shader);

    return shader;
}
