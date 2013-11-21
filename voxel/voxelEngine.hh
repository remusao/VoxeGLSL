#ifndef VOXEL_ENGINE_HH_
# define VOXEL_ENGINE_HH_

# include <vector>

# include <GL/glew.h>
# include <SFML/Window.hpp>
# include <SFML/OpenGL.hpp>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "camera.hh"
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

        void processInput(float elapsed);
        void updateVBO();
        void init_buffers();
        void init_shaders();

        // Window
        sf::Window  window_;

        // Camera
        Camera camera_;

        // Buffers
        GLuint vao_;
        GLuint vbo_;

        // Shaders
        GLProgram program_;

        // World
        World world_;

        glm::mat4 projectionMatrix_; // Store the projection matrix
        glm::mat4 viewMatrix_; // Store the view matrix
        glm::mat4 modelMatrix_; // Store the model matrix
};

#endif /* !VOXEL_ENGINE_HH_ */
