#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include "../shader.h"
#include "basicRendererEntity.h"

class SingleTriangleRenderer : public BasicRendererEntity
{
private:

public:

private:
    float vertexPosition[9] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    float vertexColor[9] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };



public:
    SingleTriangleRenderer();
    ~SingleTriangleRenderer();

    float* GetVertexPosition();
    float* GetVertexColor();

    void SetupRenderingData();
    void Draw();
    void ReadyToShutdown();
};