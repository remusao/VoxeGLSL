#ifndef VOXEL_ENGINE_HH_
# define VOXEL_ENGINE_HH_

# include <vector>

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "shader.hh"
# include "world.hh"

class VoxelEngine
{
    public:
        VoxelEngine(const char* name,
               int width,
               int height);
        ~VoxelEngine();

        void mainloop();

    private:

        void draw() const;
        void init_buffers();
        void init_shaders();

        // Window
        const char* name_;
        const int   width_;
        const int   height_;
        GLFWwindow* window_;

        // Buffers
        GLuint vao_;
        GLuint vbo_;

        // Shaders
        ShaderManager sm_;
        GLuint shaderProgram_;

        // World
        World world_;

        glm::mat4 projectionMatrix_; // Store the projection matrix
        glm::mat4 viewMatrix_; // Store the view matrix
        glm::mat4 modelMatrix_; // Store the model matrix
};

#endif /* !VOXEL_ENGINE_HH_ */
