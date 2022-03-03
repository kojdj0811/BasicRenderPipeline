#pragma once

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../engine.h"


class CameraController
{
private:
    glm::vec3 m_position;
    // glm::vec3 m_eulerAngles;

    glm::mat4 m_projection;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_mvp;

    float m_fieldOfView = 30.0f;
    float m_ratio;

public:


private:

public:
    CameraController();
    ~CameraController();
};

