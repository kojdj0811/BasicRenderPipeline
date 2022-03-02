#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include "../shader.h"


class Utility
{
private:
    static Utility* m_instance;

public:
    GLuint triangleVertexPositionBufferObjectId;
    GLuint triangleVertexColorBufferObjectId;
    GLuint triangleVertexArrayObject;
    GLuint triangleShaderProgramId;
    Shader* triangleShaderProgram;

    float triangle_position[9] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    float triangle_color[9] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

private:
    Utility();

public:
    ~Utility();

    void SetupRenderingData_SingleTriangle();
    void ReadyToShutdown_SingleTriangle();

    static Utility* GetInstance ();
    static std::string ReadStringFromFile (char* filePath);
};