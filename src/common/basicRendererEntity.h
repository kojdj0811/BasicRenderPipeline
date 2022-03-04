#pragma once

#include <iostream>
#include <fstream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader.h"


class BasicRendererEntity
{
public:
    GLuint vertexPositionBufferObjectId;
    GLuint vertexColorBufferObjectId;
    GLuint vertexArrayObject;
    GLuint shaderProgramId;
    Shader* shaderProgram;


protected:
    glm::mat4 m_mvpMatrix;


public:
    BasicRendererEntity();
    BasicRendererEntity(glm::mat4 mvpMatrix);
    virtual ~BasicRendererEntity();

    void SetMvpMatrix(glm::mat4 mvpMatrix);

    virtual void SetupRenderingData() {}
    virtual void Update(float a_deltaTime) {}
    virtual void Draw() {}
    virtual void ReadyToShutdown() {}
    virtual float* GetVertexPosition() {}
    virtual float* GetVertexColor() {}
};
