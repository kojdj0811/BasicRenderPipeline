#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utility.h"
#include "../shader.h"


class BasicRendererEntity
{
public:
    std::string entityName;

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
    GLfloat* m_vertexColorBuffer;
    GLuint* m_indexBuffer;

private:
    static std::vector<BasicRendererEntity*> m_allRendererEntities;



public:
    static void UpdateAllRendererEntities ();


public:
    BasicRendererEntity ();
    // BasicRendererEntity (std::string entityName);
    // BasicRendererEntity (std::string entityName, glm::mat4 mvpMatrix);
    BasicRendererEntity (glm::mat4 mvpMatrix);
    virtual ~BasicRendererEntity ();

    virtual void SetupRenderingData () {}
    virtual void Update (float a_deltaTime) {}
    virtual void Draw () {}
    virtual void ReadyToShutdown () {}

    GLfloat* GetVertexBuffer () { return m_vertexBuffer; }
    GLuint* GetIndexBuffer () { return m_indexBuffer; }
    GLfloat* GetVertexColorBuffer () { return m_vertexColorBuffer; }


    void SetMvpMatrix (glm::mat4 mvpMatrix) { m_mvpMatrix = mvpMatrix; }
    void SetProjectionMatrix (glm::mat4 projectionMatrix) { m_projectionMatrix = projectionMatrix; }
    void SetViewMatrix (glm::mat4 viewMatrix) { m_viewMatrix = viewMatrix; }
    void SetModelMatrix (glm::mat4 modelMatrix) { m_modelMatrix = modelMatrix; }

    void SetPosition (glm::vec3 position) { m_position = position; }
    void SetEulerAngles (glm::vec3 eulerAngles) { m_eulerAngles = eulerAngles; }
    void LookAt (glm::vec3 target) { LookAt(target, glm::vec3(0.0f, 1.0f, 0.0f)); }
    void LookAt (glm::vec3 target, glm::vec3 worldUp);

    glm::mat4 getMvpMatrix () { return m_mvpMatrix; }
    glm::mat4 getProjectionMatrix () { return m_projectionMatrix; }
    glm::mat4 getViewMatrix () { return m_viewMatrix; }
    glm::mat4 getModelMatrix () { return m_modelMatrix; }

    glm::vec3 GetPosition () { return m_position; }
    glm::vec3 GetEulerAngles () { return m_eulerAngles; }
    glm::vec3 GetUp () { return m_up; }
    glm::vec3 GetForward () { return m_forward; }
    // glm::vec3 GetLeft () {  }
};
