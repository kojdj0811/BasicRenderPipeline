#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "utility.h"
#include "../shader.h"


class BasicRendererEntity
{
public:


protected:
    std::string m_entityName;

    GLuint  m_vertexPositionBufferObjectId;
    GLuint  m_vertexColorBufferObjectId;
    GLuint  m_vertexArrayObject;
    GLuint  m_shaderProgramId;
    Shader* m_shaderProgram;

    glm::mat4 m_mvpMatrix;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;

    glm::vec3 m_position;
    glm::vec3 m_eulerAngles;
    glm::quat m_rotation;
    glm::vec3 m_scale;
    glm::vec3 m_skew;
    glm::vec3 m_up;
    glm::vec3 m_forward;
    glm::vec4 m_perspective;


    GLfloat* m_vertexBuffer;
    GLfloat* m_vertexColorBuffer;
    GLuint*  m_indexBuffer;

private:
    static std::vector<BasicRendererEntity*> m_allRendererEntities;




public: //static
    static void UpdateAllRendererEntities ();


private:
    void initialize ();
    void decomposeModelMatrix (const glm::mat4& targetMatrix);

public:
    BasicRendererEntity ();
    BasicRendererEntity (std::string entityName);
    BasicRendererEntity (glm::mat4 mvpMatrix);
    BasicRendererEntity (std::string entityName, glm::mat4 mvpMatrix);

    virtual ~BasicRendererEntity ();



    virtual void SetupRenderingData () {}
    virtual void Update (float a_deltaTime) {}
    virtual void Draw () {}
    virtual void ReadyToShutdown () {}

    const GLfloat*  GetVertexBuffer         () { return m_vertexBuffer; }
    const GLuint*   GetIndexBuffer          () { return m_indexBuffer; }
    const GLfloat*  GetVertexColorBuffer    () { return m_vertexColorBuffer; }

    const glm::mat4& GetMvpMatrix           () { return m_mvpMatrix; }
    const glm::mat4& GetProjectionMatrix    () { return m_projectionMatrix; }
    const glm::mat4& GetViewMatrix          () { return m_viewMatrix; }
    const glm::mat4& GetModelMatrix         () { return m_modelMatrix; }

    const glm::vec3& GetPosition            () { return m_position; }
    const glm::vec3& GetEulerAngles         () { return m_eulerAngles; }
    const glm::vec3& GetUp                  () { return m_up; }
    const glm::vec3& GetForward             () { return m_forward; }
    // glm::vec3 GetLeft () {  }


    void SetMvpMatrix           (const glm::mat4& mvpMatrix)        { decomposeModelMatrix(mvpMatrix); }
    void SetProjectionMatrix    (const glm::mat4& projectionMatrix) { m_projectionMatrix = projectionMatrix; }
    void SetViewMatrix          (const glm::mat4& viewMatrix)       { m_viewMatrix = viewMatrix; }
    void SetModelMatrix         (const glm::mat4& modelMatrix)      { m_modelMatrix = modelMatrix; }

    void SetPosition            (const glm::vec3& position);
    void SetEulerAngles         (const glm::vec3& eulerAngles);
    void LookAt                 (const glm::vec3& target)           { LookAt(target, glm::vec3(0.0f, 1.0f, 0.0f)); }
    void LookAt                 (const glm::vec3& target, const glm::vec3& worldUp);
};
