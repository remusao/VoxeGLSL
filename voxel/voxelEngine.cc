#include <iostream>

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
      projectionMatrix_(glm::perspective(60.0f, (float)width / (float)height, 0.1f, 100.f)),
      viewMatrix_(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f))),
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

    // Populate world
    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j)
            world_.addVoxel(Voxel(i, j, 0));
}


VoxelEngine::~VoxelEngine()
{
    // Delete buffers
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}


void VoxelEngine::mainloop()
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
            }
        }

        // Process input
        processInput(elapsed.asSeconds());

        // Update elapsed time
        elapsed = time;

        // Update Vertex Buffer Object
        updateVBO();

        // Update camera transformation
        program_.addUniform("camera", camera_.matrix());

        // Draw
        glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glDrawArrays(GL_LINE_LOOP, 0, world_.size());

        // swap buffers
        window_.display();
    }
}

void VoxelEngine::processInput(float elapsed)
{
    const float moveSpeed = 0.1;
    const float rotationSpeed = 0.5;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camera_.offsetPosition(elapsed * moveSpeed * -camera_.forward());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camera_.offsetPosition(elapsed * moveSpeed * camera_.forward());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camera_.offsetPosition(elapsed * moveSpeed * -camera_.right());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camera_.offsetPosition(elapsed * moveSpeed * camera_.right());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        camera_.offsetPosition(elapsed * moveSpeed * -glm::vec3(0, 1, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        camera_.offsetPosition(elapsed * moveSpeed * glm::vec3(0, 1, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        camera_.offsetOrientation(-rotationSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        camera_.offsetOrientation(rotationSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        camera_.offsetOrientation(0, -rotationSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        camera_.offsetOrientation(0, rotationSpeed);
}

void VoxelEngine::updateVBO()
{
    size_t size = world_.size() * 3;
    float* array = new float[size];

    // For each cube push its position
    for (size_t i = 0; i < world_.size(); ++i)
    {
        Voxel v = world_.getVoxel(i);
        array[i * 3] = v.getx();
        array[i * 3 + 1] = v.gety();
        array[i * 3 + 2] = v.getz();
    }

    // Fill VBO with cube vertices
    glBufferData(GL_ARRAY_BUFFER, size * sizeof (float), array, GL_STATIC_DRAW);
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
    // program_.addShader("shaders/geometry.shader", GL_GEOMETRY_SHADER);

    program_.finalize();

    program_.addAttribute("position", 3, GL_FLOAT, GL_FALSE, 0, 0);

    program_.addUniform("camera", camera_.matrix());
    program_.addUniform("m", modelMatrix_);
}
