#pragma onece

#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include "../shader.h"


class BasicRendererEntity
{
public:
    GLuint vertexPositionBufferObjectId;
    GLuint vertexColorBufferObjectId;
    GLuint vertexArrayObject;
    GLuint shaderProgramId;
    Shader* shaderProgram;


private:


public:
    BasicRendererEntity();
    virtual ~BasicRendererEntity();

    virtual void SetupRenderingData() {}
    virtual void Draw() {}
    virtual void ReadyToShutdown() {}
    virtual float* GetVertexPosition() {}
    virtual float* GetVertexColor() {}
};
