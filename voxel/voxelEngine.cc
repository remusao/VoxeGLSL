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

    //
    // Callbacks
    //

    void key_callback(GLFWwindow* window, int key, int, int action, int)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }


}

VoxelEngine::VoxelEngine(const char* name, int width, int height)
    : name_(name),
      width_(width),
      height_(height),
      projectionMatrix_(glm::perspective(60.0f, (float)width / (float)height, 0.1f, 100.f)),
      viewMatrix_(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f))),
      modelMatrix_(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)))
{
    // Version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Init library
    if (!glfwInit())
    {
        throw EngineException();
    }

    // Specify options to OpenGL
    init_rendering();

    // Create window
    window_ = glfwCreateWindow(width_, height_, name_, glfwGetPrimaryMonitor(), NULL);
    if (!window_)
    {
        glfwTerminate();
        throw EngineException();
    }

    // Make the window's context current
    glfwMakeContextCurrent(window_);

    // Init glew
    glewExperimental = GL_TRUE;
    glewInit();

    // Print infos about OpenGL version
    print_opengl_info();

    // Set callbacks
    glfwSetKeyCallback(window_, key_callback);

    init_buffers();
    init_shaders();
}


VoxelEngine::~VoxelEngine()
{
    // Delete shaders
    glDeleteProgram(shaderProgram_);

    // Delete buffers
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);

    glfwDestroyWindow(window_);
    glfwTerminate();
}


void VoxelEngine::mainloop()
{
    // Main loop
    while (!glfwWindowShouldClose(window_))
    {
        // Draw world
        draw();

        //display(world);
        glfwSwapBuffers(window_);

        /* Poll for and process events */
        glfwPollEvents();
    }
}


void VoxelEngine::draw() const
{
    // Clear the screen to black
    glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void VoxelEngine::init_buffers()
{
    // Load cube into buffer
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube::vertices), cube::vertices, GL_STATIC_DRAW);
}


void VoxelEngine::init_shaders()
{
    // Create and compile shaders
    GLuint vertexShader = sm_.fromfile("shaders/vertex.shader", GL_VERTEX_SHADER);
    GLuint fragmentShader = sm_.fromfile("shaders/fragment.shader", GL_FRAGMENT_SHADER);

    // Link the vertex and fragment shader into a shader program
    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragmentShader);
    glBindFragDataLocation(shaderProgram_, 0, "color");
    glLinkProgram(shaderProgram_);
    glUseProgram(shaderProgram_);
    

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram_, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    int pLoc = glGetUniformLocation(shaderProgram_, "p"); // Get the location of our projection matrix in the shader
    int vLoc = glGetUniformLocation(shaderProgram_, "v"); // Get the location of our view matrix in the shader
    int mLoc = glGetUniformLocation(shaderProgram_, "m"); // Get the location of our model matrix in the shader

    glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix_[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, &viewMatrix_[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix_[0][0]); // Send our model matrix to the shader
}
