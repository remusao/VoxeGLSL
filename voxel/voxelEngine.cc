#include <iostream>
#include <string>

#include "voxelEngine.hh"
#include "cube.hh"
#include "exceptions.hh"

namespace
{
    void print_opengl_info()
    {
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);
        std::cout << "Renderer: " << renderer << std::endl;
        std::cout << "OpenGL version: " << version << std::endl;
    }
}


VoxelEngine::VoxelEngine(const char* name, int width, int height)
    : window_(sf::VideoMode(width, height), name, sf::Style::Default, sf::ContextSettings(32)),
      wireframe_(GL_FILL),
      modelMatrix_(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)))
{
    // Window options
    window_.setVerticalSyncEnabled(true);

    // Init Glew
    glewExperimental = GL_TRUE;
    glewInit();

    // Specify options to OpenGL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    // Print infos about OpenGL version
    print_opengl_info();

    // Init buffers and shaders
    program_.init();
    init_buffers();
    init_shaders();

    // Init camera
    camera_.setPosition(glm::vec3(0, 0, 5));
    camera_.setViewportAspectRatio(window_.getSize().x / window_.getSize().y);
    camera_.setNearAndFarPlanes(0.01, 3000.0);
}


VoxelEngine::~VoxelEngine()
{
    // Delete buffers
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}

void VoxelEngine::populate(std::function<void(World&)> init)
{
    init(world_);
    updateVBO();
}

void VoxelEngine::loop(std::function<bool(World&)> update)
{
    sf::Clock clock;
    sf::Time elapsed = clock.getElapsedTime();
    bool running = true;

    while (running)
    {
        sf::Time time = clock.getElapsedTime();

        // handle events
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
                break;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    running = false;
                    break;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    glPolygonMode(GL_FRONT_AND_BACK, wireframe_);
                    wireframe_ = (wireframe_ == GL_FILL ? GL_LINE : GL_FILL);
                }
            }
        }

        // Process input
        processInput(elapsed.asSeconds());

        // Update frustum
        frustum_.setCamInternals(camera_.fieldOfViewR(), camera_.ratio(), camera_.nearPlane(), camera_.farPlane());
        frustum_.setCamDef(camera_.position(), camera_.forward(), camera_.up(), camera_.right());

        // Update world
        if (update(world_))
        {
            updateVBO();
        }

        // frame per second
        float fps = 1.f / (time.asSeconds() - elapsed.asSeconds());
        std::cout << fps << std::endl;

        // Update elapsed time
        elapsed = time;

        // Update Vertex Buffer Object
        // updateVBO();

        // Update model view projection matrix
        program_.addUniform("mvp", camera_.matrix() * modelMatrix_);

        // Draw
        glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, world_.size());

        // swap buffers
        window_.display();
    }
}

void VoxelEngine::processInput(float elapsed)
{
    const float moveSpeed = 0.1;
    const float rotationSpeed = 1.0;

    // Z-axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camera_.offsetPosition(elapsed * moveSpeed * -camera_.forward());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camera_.offsetPosition(elapsed * moveSpeed * camera_.forward());

    // Y-axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camera_.offsetPosition(elapsed * moveSpeed * -camera_.right());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camera_.offsetPosition(elapsed * moveSpeed * camera_.right());

    // X-axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        camera_.offsetPosition(elapsed * moveSpeed * -glm::vec3(0, 1, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        camera_.offsetPosition(elapsed * moveSpeed * glm::vec3(0, 1, 0));

    // Rotation arround X-axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        camera_.offsetOrientation(-rotationSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        camera_.offsetOrientation(rotationSpeed, 0);

    // Rotation arround Y-axis
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        camera_.offsetOrientation(0, -rotationSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        camera_.offsetOrientation(0, rotationSpeed);
}

void VoxelEngine::updateVBO()
{
    float* array = new float[world_.size() * 3];
    size_t size = 0;

    // For each cube push its position
    for (size_t i = 0; i < world_.size(); ++i)
    {
        Voxel v = world_.getVoxel(i);
       if (frustum_.culling(v.getPos()))
       {
            array[size * 3] = v.getx();
            array[size * 3 + 1] = v.gety();
            array[size * 3 + 2] = v.getz();
            ++size;
       }
    }

    std::cout << "World size: " << size << " Voxels" << std::endl;
    std::cout << "=> " << size * 12 << " triangles" << std::endl;


    // Fill VBO with cube vertices
    glBufferData(GL_ARRAY_BUFFER, 3 * size * sizeof (float), array, GL_STATIC_DRAW);
    delete [] array;
}


void VoxelEngine::init_buffers()
{
    // Create VAO
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // Create VBO
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
}


void VoxelEngine::init_shaders()
{
    program_.addShader("shaders/vertex.shader", GL_VERTEX_SHADER);
    program_.addShader("shaders/fragment.shader", GL_FRAGMENT_SHADER);
    program_.addShader("shaders/geometry.shader", GL_GEOMETRY_SHADER);

    program_.finalize();

    program_.addAttribute("position", 3, GL_FLOAT, GL_FALSE, 0, 0);
}
