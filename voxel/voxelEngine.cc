#include <iostream>

#include "voxelEngine.hh"
#include "cube.hh"
#include "exceptions.hh"

namespace
{
    void init_rendering()
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc (GL_LESS);
    }

    void print_opengl_info()
    {
        const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
        const GLubyte* version = glGetString (GL_VERSION); // version as a string
        std::cout << "Renderer: " << renderer << std::endl;
        std::cout << "OpenGL version: " << version << std::endl;
    }
}

VoxelEngine::VoxelEngine(const char* name, int width, int height)
    : name_(name),
      width_(width),
      height_(height),
      window_(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, sf::ContextSettings(32)),
      projectionMatrix_(glm::perspective(60.0f, (float)width / (float)height, 0.1f, 100.f)),
      viewMatrix_(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f))),
      modelMatrix_(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)))
{
    window_.setVerticalSyncEnabled(true);

    // Specify options to OpenGL
    init_rendering();

    glewExperimental = GL_TRUE;
    glewInit();

    // Print infos about OpenGL version
    print_opengl_info();

    init_buffers();
    init_shaders();

    // Populate world
    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j)
            world_.addVoxel(Voxel(i, j, 0));
}


VoxelEngine::~VoxelEngine()
{
    // Delete shaders
    glDeleteProgram(shaderProgram_);

    // Delete buffers
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}


void VoxelEngine::mainloop()
{
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (!processEvent(event))
            {
                running = false;
                break;
            }
        }

        // Draw world
        updateVBO();
        draw();

        // swap buffers
        window_.display();
    }
}

bool VoxelEngine::processEvent(const sf::Event& e)
{
    if (e.type == sf::Event::Closed)
    {
        return false;
    }
    else if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Escape)
        {
            return false;
        }
    }
    return true;
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

void VoxelEngine::draw() const
{
    // Clear the screen to black
    glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDrawArrays(GL_LINE_LOOP, 0, world_.size());
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
    // Create and compile shaders
    GLuint vertexShader = sm_.fromfile("shaders/vertex.shader", GL_VERTEX_SHADER);
    GLuint fragmentShader = sm_.fromfile("shaders/fragment.shader", GL_FRAGMENT_SHADER);
    // GLuint geometryShader = sm_.fromfile("shaders/fragment.shader", GL_GEOMETRY_SHADER);

    // Link the vertex and fragment shader into a shader program
    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragmentShader);
    // glAttachShader(shaderProgram_, geometryShader);
    glBindFragDataLocation(shaderProgram_, 0, "color");
    glLinkProgram(shaderProgram_);
    glUseProgram(shaderProgram_);
    
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram_, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Set uniforms to use in shaders
    int pLoc = glGetUniformLocation(shaderProgram_, "p");
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix_[0][0]);
    int vLoc = glGetUniformLocation(shaderProgram_, "v");
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, &viewMatrix_[0][0]);
    int mLoc = glGetUniformLocation(shaderProgram_, "m");
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix_[0][0]);
}
