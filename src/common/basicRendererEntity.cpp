#include "basicRendererEntity.h"

std::vector<BasicRendererEntity*> BasicRendererEntity::m_allRendererEntities;


void BasicRendererEntity::initialize () {
    m_allRendererEntities.push_back(this);
    m_shaderProgram = new Shader();
}

void BasicRendererEntity::decomposeModelMatrix (const glm::mat4& targetMatrix) {
    m_mvpMatrix = targetMatrix;
    glm::decompose(targetMatrix, m_scale, m_rotation, m_position, m_skew, m_perspective);
}

BasicRendererEntity::BasicRendererEntity() {
    initialize();
    m_entityName = "BasicRendererEntity";
}

BasicRendererEntity::BasicRendererEntity(std::string entityName) {
    initialize();
    m_entityName = entityName;
}

BasicRendererEntity::BasicRendererEntity(glm::mat4 mvpMatrix) {
    initialize();
    m_entityName = "BasicRendererEntity";
    m_mvpMatrix = mvpMatrix;
}

BasicRendererEntity::BasicRendererEntity(std::string entityName, glm::mat4 mvpMatrix)
{
    initialize();
    m_entityName = entityName;
    m_mvpMatrix = mvpMatrix;
}


BasicRendererEntity::~BasicRendererEntity()
{
    SAFE_DELETE(m_shaderProgram);
    SAFE_DELETE(m_vertexBuffer);
    SAFE_DELETE(m_vertexColorBuffer);
    SAFE_DELETE(m_indexBuffer);

    int allRendererEntitiesSize = m_allRendererEntities.size();
    for(int i = 0; i < allRendererEntitiesSize; i++) {
        if(m_allRendererEntities[i] == this) {
            m_allRendererEntities.erase(m_allRendererEntities.begin() + i);
            break;
        }
    }

    fprintf(stderr, "Destroyed :: %s\n", m_entityName.c_str());
}




void BasicRendererEntity::SetPosition (const glm::vec3& position) {
    m_position = position;

    glm::vec4 previousPosition = m_modelMatrix[3];
    m_modelMatrix[3] = glm::vec4(
        position[0] * m_scale[0],
        position[1] * m_scale[1],
        position[2] * m_scale[2],
        previousPosition[4]
    );
}

void BasicRendererEntity::SetEulerAngles (const glm::vec3& eulerAngles) {
    m_eulerAngles = eulerAngles;
}


void BasicRendererEntity::LookAt (const glm::vec3& target, const glm::vec3& worldUp) {
    m_viewMatrix = glm::lookAt(
        m_position,
        target,
        worldUp
    );

    m_forward = glm::normalize(target - m_position);
}
