#ifndef VOXEL_ENGINE_HH_
# define VOXEL_ENGINE_HH_

# include <vector>
# include <functional>

# include <GL/glew.h>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
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

        // Populate world with Voxels
        void populate(std::function<void(World&)>);

        // Main Loop (update world at each loop and redraw if needed)
        void loop(std::function<bool(World&)>);

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

        glm::mat4 modelMatrix_; // Store the projection matrix
};

#endif /* !VOXEL_ENGINE_HH_ */
