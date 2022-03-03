#include "cameraController.h"

CameraController::CameraController()
{
    Engine* _engine = Engine::GetInstance();

    glm::ivec2 screenSize = _engine->GetScreenSize();
    m_ratio = (float)screenSize.x / (float)screenSize.y;

    m_projection = glm::perspective(
        glm::radians(m_fieldOfView),
        m_ratio,
        0.01f,
        1000.0f
    );

    // m_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);

    m_position = glm::vec3(0.0f, 0.0f, -1.0f);

    m_viewMatrix = glm::lookAt(
        m_position,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    m_modelMatrix = glm::mat4(1.0f);
    m_mvp = m_projection * m_viewMatrix, m_modelMatrix;
}

CameraController::~CameraController()
{
}
