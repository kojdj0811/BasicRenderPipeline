#include "basicRendererEntity.h"



BasicRendererEntity::BasicRendererEntity()
{
    shaderProgram = new Shader();
}

BasicRendererEntity::~BasicRendererEntity()
{
    delete shaderProgram;
}