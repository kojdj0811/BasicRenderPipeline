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
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;

    glm::vec3 m_position;
    glm::vec3 m_eulerAngles;
    glm::vec3 m_up;
    glm::vec3 m_forward;


    GLfloat* m_vertexBuffer;
    GLuint* m_indexBuffer;

    GLuint m_vertexBufferSize;
    GLuint m_indexBufferSize;


public:
    BasicRendererEntity ();
    BasicRendererEntity (glm::mat4 mvpMatrix);
    virtual ~BasicRendererEntity ();

    virtual void SetupRenderingData () {}
    virtual void Update (float a_deltaTime) {}
    virtual void Draw () {}
    virtual void ReadyToShutdown () {}
    virtual float* GetVertexPosition () {}
    virtual float* GetVertexColor () {}


    void SetMvpMatrix (glm::mat4 mvpMatrix);
    void SetProjectionMatrix (glm::mat4 mvpMatrix);
    void SetViewMatrix (glm::mat4 mvpMatrix);
    void SetModelMatrix (glm::mat4 mvpMatrix);

    void SetPosition (glm::vec3);
    void SetEulerAngles (glm::vec3);
    void SetUp (glm::vec3);
    void SetForward (glm::vec3);

    glm::mat4 getMvpMatrix ();
    glm::mat4 getProjectionMatrix ();
    glm::mat4 getViewMatrix ();
    glm::mat4 getModelMatrix ();

    glm::vec3 GetPosition ();
    glm::vec3 GetEulerAngles ();
    glm::vec3 GetUp ();
    glm::vec3 GetForward ();
};
