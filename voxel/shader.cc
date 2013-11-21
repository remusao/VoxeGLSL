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

GLuint ShaderManager::fromfile(const char*, GLenum)
{
    return 0;
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
        throw ShaderException();
    }

    // Add id to shader list
    shaders_.emplace_back(shader);

    return shader;
}



namespace shader
{
    // Vertex shader
    const GLchar* vertex = R"(
        #version 150 core

        in vec3 position;
        in vec3 color;
        in vec2 texcoord;

        out vec3 Color;
        out vec2 Texcoord;

        void main()
        {
            Color = color;
            Texcoord = texcoord;
            gl_Position = vec4(position, 1.0);
        }
    )";

    // Fragment shader
    const GLchar* fragment = R"(
        #version 150 core

        in vec3 Color;
        in vec2 TexCoord;

        out vec4 outColor;

        void main()
        {
            outColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )";

}
