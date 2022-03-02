#pragma one

// System libs.
#include <iostream>

// Include libs.
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>

// Header includes.
// TODO: Include your headers here...
#include "common/utility.h"

// Function prototypes.
void WindowResize(GLFWwindow* a_window, int a_width, int a_height);

// Classes.
class Engine
{
public:
    int Initialize();
    static void errorCallback (int errorCode, const char* errorDescription);
    float gameSpeed = 0.1f;
    int fps = 0;

private:
    int screenWidth = 800;
    int screenHeight = 600;

    const char* windowName = "Default Name";

    GLFWwindow* window;

    // Game loop.
    float lastFrameTime = 0.0f;
    glm::vec3 clearColor = glm::vec3(0.2f, 0.3f, 0.3f);
    float lastFpsTime = 0.0f;

public:
    Engine(int a_width, int a_height, const char* a_windowName);

    void Update(float a_deltaTime);
    void Draw();
    void Shutdown();

    void ProcessInput(GLFWwindow* a_window);

private:
    // OpenGL
    void SetupOpenGlRendering();

private:
    void SetupRenderingData();
};