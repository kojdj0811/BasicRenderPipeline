#pragma once

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../engine.h"


class CameraController
{
private:
    glm::vec3 m_position;
    // glm::vec3 m_eulerAngles;
    glm::vec3 m_up;
    glm::vec3 m_forward;

    glm::vec3 m_worldUp;



    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    // glm::mat4 m_modelMatrix;

    float m_fieldOfView = 30.0f;
    float m_ratio;

public:


private:

public:
    CameraController(glm::vec3 position);
    ~CameraController();

    glm::vec3 GetPosition();    
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
    glm::mat4 GetMvpMatrix(glm::mat4 modelMatrix);

    void SetPosition (glm::vec3 position);
    void LookAt (glm::vec3 position);

    glm::vec3 GetLeft();
};

