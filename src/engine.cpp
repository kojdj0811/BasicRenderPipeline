#include "engine.h"
#include "shader.h"


Engine::Engine(int a_width, int a_height, const char* a_windowName)
{
    this->screenWidth = a_width;
    this->screenHeight = a_height;
    this->windowName = a_windowName;
}

void Engine::errorCallback (int errorCode, const char* errorDescription) {
    fprintf(stderr, "Error(%d): %s\n", errorCode, errorDescription);
}

int Engine::Initialize()
{
    glfwSetErrorCallback(errorCallback);

    // Initialize GLFW.
    glfwInit();

    // Tell GLFW that we want to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tell GLFW that we want to use the OpenGL's core profile.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Do this for mac compatability.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //anti aliasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSwapInterval(1);

    // Create Window.

    // Instantiate the window object.
    this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, this->windowName, NULL, NULL);

    // Make sure that the window is created.
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();

        std::cin.get();
        return 0;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD.

    // Make sure that glad has been initialized successfully.
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        
        std::cin.get();
        return 0;
    }


    // error
    std::cout << "OpenGL version" << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vender" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer" << glGetString(GL_RENDERER) << std::endl;



    // Set the viewport
    glViewport(0, 0, this->screenWidth, this->screenHeight);

    // Setup callbacks.

    // Binds the 'framebuffer_size_callback' method to the window resize event.
    glfwSetFramebufferSizeCallback(window, WindowResize);

    this->SetupOpenGlRendering();

    this->SetupRenderingData();

    // Start game loop.
    while(!glfwWindowShouldClose(this->window))
    {
        // Calculate the elapsed time between the current and previous frame.
        float m_frameTime = (float)glfwGetTime();
        float m_deltaTime = m_frameTime - this->lastFrameTime;
        this->lastFrameTime = m_frameTime;


        fps++;
        if(m_frameTime - lastFpsTime >= 1.0f) {
            printf("%f ms/frame %d fps\n", 1000.0/fps, fps);
            fps = 0;
            lastFpsTime = m_frameTime;
        }


        glfwPollEvents();
        this->ProcessInput(this->window);

        glClearColor(this->clearColor.x, this->clearColor.y, this->clearColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Application logic
        this->Update(m_deltaTime);
        this->Draw();

        glfwSwapBuffers(this->window);
    }




    glUseProgram(0);
    glBindVertexArray(0);


    Utility::GetInstance()->ReadyToShutdown_SingleTriangle();


    glfwTerminate();

    return 1;
}

void WindowResize(GLFWwindow* a_window, int a_width, int a_height)
{
    glViewport(0, 0, a_width, a_height);
    std::cout << "WindowResized :: " << a_width << ", " << a_height << std::endl;
    // TODO: Do your resize logic here...
}

void Engine::ProcessInput(GLFWwindow* a_window)
{
    // TODO: Process your input here...

    // If the escape key gets pressed, close the window.
    if(glfwGetKey(a_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(a_window, true);
}

void Engine::SetupOpenGlRendering()
{
    return;
    // TODO: Setup OpenGL code here...
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

}

void Engine::SetupRenderingData () {
    Utility* _utility = Utility::GetInstance();

    _utility->SetupRenderingData_SingleTriangle();
}


void Engine::Update(float a_deltaTime)
{
    // TODO: Update your logic here...
}

void Engine::Draw()
{
    // TODO: Render your stuff here...
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Engine::Shutdown () {
    
}