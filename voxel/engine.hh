#ifndef ENGINE_HH_
# define ENGINE_HH_

# include <vector>

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include "shader.hh"
# include "world.hh"

class Engine
{
    public:
        Engine(const char* name,
               int width,
               int height);
        ~Engine();

        void mainloop();

    private:

        void draw() const;
        void init_buffers();
        void init_shaders();

        // Window
        const char* name_;
        int         width_;
        int         height_;
        GLFWwindow* window_;

        // Buffers
        GLuint vao_;
        GLuint vbo_;

        // Shaders
        ShaderManager sm_;
        GLuint shaderProgram_;

        // World
        World world_;
};

#endif /* !ENGINE_HH_ */
