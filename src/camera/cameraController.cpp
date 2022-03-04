#include "cameraController.h"

CameraController::CameraController(glm::vec3 position)
{
    Engine* _engine = Engine::GetInstance();

    glm::ivec2 screenSize = _engine->GetScreenSize();
    m_ratio = (float)screenSize.x / (float)screenSize.y;

    // perspective
    m_projectionMatrix = glm::perspective(
        glm::radians(m_fieldOfView),
        m_ratio,
        0.01f,
        1000.0f
    );

    // ortho
    // m_projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);

    m_position = position;
    m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_forward = glm::vec3(0.0f, 0.0f, 1.0f);


    LookAt(m_position + m_forward);
}

CameraController::~CameraController()
{
}

glm::vec3 CameraController::GetPosition () {
    return m_position;
}

glm::mat4 CameraController::GetProjectionMatrix () {
    return m_projectionMatrix;
}

glm::mat4 CameraController::GetViewMatrix () {
    return m_viewMatrix;
}

glm::mat4 CameraController::GetMvpMatrix (glm::mat4 modelMatrix) {
    return m_projectionMatrix * m_viewMatrix * modelMatrix;
}


void CameraController::SetPosition (glm::vec3 position) {
    m_viewMatrix = glm::translate(glm::mat4(), position - m_position) * m_viewMatrix;

    LookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    fprintf(stderr, "(%f, %f, %f) > (%f, %f, %f)\n", m_position.x, m_position.y, m_position.z, position.x, position.y, position.z);

    m_position = position;
}



void CameraController::LookAt (glm::vec3 target) {
    m_viewMatrix = glm::lookAt(
        m_position,
        target,
        m_worldUp
    );

// setup m_forward, m_up
    m_forward = glm::normalize(target - m_position);
}

// glm::vec3 GetLeft() {
//     return m_viewMatrix
// }
