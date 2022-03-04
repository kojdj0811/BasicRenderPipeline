#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include "../shader.h"
#include "basicRendererEntity.h"

class SingleQuadRenderer : public BasicRendererEntity
{
private:

public:

private:
    float vertexPosition[12] = {
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    float vertexColor[12] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    GLuint indexBuffer[6] = {
        0, 1, 3,
        3, 1, 2
    };


public:
    SingleQuadRenderer();
    SingleQuadRenderer(glm::mat4 mvpMatrix);
    ~SingleQuadRenderer();

    float* GetVertexPosition();
    float* GetVertexColor();

    void SetupRenderingData();
    void Update(float a_deltaTime);
    void Draw();
    void ReadyToShutdown();
};