#include "basicRendererEntity.h"



BasicRendererEntity::BasicRendererEntity() {
    shaderProgram = new Shader();
}

BasicRendererEntity::BasicRendererEntity(glm::mat4 mvpMatrix)
{
    m_mvpMatrix = mvpMatrix;
    shaderProgram = new Shader();
}

BasicRendererEntity::~BasicRendererEntity()
{
    delete shaderProgram;
}


void BasicRendererEntity::SetMvpMatrix (glm::mat4 mvpMatrix) {
    m_mvpMatrix = mvpMatrix;
}