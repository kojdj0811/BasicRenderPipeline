#include "basicRendererEntity.h"

std::vector<BasicRendererEntity*> BasicRendererEntity::m_allRendererEntities;


BasicRendererEntity::BasicRendererEntity() {
    m_allRendererEntities.push_back(this);

    shaderProgram = new Shader();
}

BasicRendererEntity::BasicRendererEntity(glm::mat4 mvpMatrix)
{
    m_allRendererEntities.push_back(this);

    m_mvpMatrix = mvpMatrix;
    shaderProgram = new Shader();
}

BasicRendererEntity::~BasicRendererEntity()
{
    delete shaderProgram;

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

    fprintf(stderr, "Destroyed :: %s\n", entityName.empty() ? "Nan" : entityName);
}

void BasicRendererEntity::LookAt (glm::vec3 target, glm::vec3 worldUp) {
    m_viewMatrix = glm::lookAt(
        m_position,
        target,
        worldUp
    );

    m_forward = glm::normalize(target - m_position);
}
