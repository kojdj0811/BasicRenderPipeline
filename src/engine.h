#pragma once

// System libs.
#include <iostream>

// Include libs.
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>

// Header includes.
// TODO: Include your headers here...
#include "shader.h"

#include "camera/cameraController.h"
#include "common/utility.h"
#include "common/basicRendererEntity.h"
#include "common/singleTriangleRenderer.h"
#include "common/singleQuadRenderer.h"

#include "common/input/mouseInput.h"

// Function prototypes.
void WindowResize(GLFWwindow* a_window, int a_width, int a_height);
class CameraController;

// Classes.
class Engine
{
public:
    GLFWwindow* window;
    glm::vec3 clearColor = glm::vec3(0.2f, 0.3f, 0.3f);

    float gameSpeed = 0.1f;
    int fps = 0;

    MouseInput* mouseInput;


private:
    static Engine* m_instance;
    int screenWidth = 800;
    int screenHeight = 600;

    const char* windowName = "Default Name";


    CameraController* m_cameraController;
    SingleQuadRenderer* m_rendererEntity;


    // Game loop.
    float lastFrameTime = 0.0f;
    float lastFpsTime = 0.0f;

public:
    Engine(int a_width, int a_height, const char* a_windowName);
    ~Engine();
    static Engine* GetInstance ();

    int Initialize();
    void InitializeSceneObjects();
    void Update(float a_deltaTime);
    void Draw();
    void Shutdown();

    void ProcessInput(GLFWwindow* a_window);
    static void errorCallback (int errorCode, const char* errorDescription);

    glm::ivec2 GetScreenSize();

private:
    // OpenGL
    void SetupOpenGlRendering();

private:
    void SetupRenderingData();
};
