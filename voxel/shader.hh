#ifndef SHADER_HH_
# define SHADER_HH_

# include <vector>

# include <GL/glew.h>
# include <GLFW/glfw3.h>

class ShaderManager
{
    public:
        ShaderManager();
        ~ShaderManager();

        ShaderManager(const ShaderManager&) = delete;
        ShaderManager& operator=(const ShaderManager&) = delete;

        ShaderManager(ShaderManager&&) = default;
        ShaderManager& operator=(ShaderManager&&) = default;

        GLuint fromfile(const char* file, GLenum shaderType);
        GLuint fromstring(const GLchar* shader, GLenum shaderType);

    private:
        std::vector<GLuint> shaders_;
};

#endif /* !SHADER_HH_ */
