#include "singleTriangleRenderer.h"



SingleTriangleRenderer::SingleTriangleRenderer() : BasicRendererEntity()
{

}

SingleTriangleRenderer::~SingleTriangleRenderer()
{
}


float* SingleTriangleRenderer::GetVertexPosition() {
    return vertexPosition;
}


float* SingleTriangleRenderer::GetVertexColor() {
    return vertexColor;
}



void SingleTriangleRenderer::SetupRenderingData () {
    //define shader
    m_shaderProgram->setVertexShader("src/shaders/simpleVertexShader.glsl");
    m_shaderProgram->setFragmentShader("src/shaders/simpleFragmentShader.glsl");
    m_shaderProgramId = m_shaderProgram->compile();

    //setup triangle data
    glGenBuffers(1, &m_vertexPositionBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);

    glGenBuffers(1, &m_vertexColorBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexColorBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);

    //use activate
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);


    GLuint positionAttribute = m_shaderProgram->getAttribLocation("positionAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBufferObjectId);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    GLuint colorAttribute = m_shaderProgram->getAttribLocation("colorAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexColorBufferObjectId);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttribute);

    glBindVertexArray(0);



    m_shaderProgram->use();
    glBindVertexArray(m_vertexArrayObject);
}

void SingleTriangleRenderer::Update(float a_deltaTime) {
}

void SingleTriangleRenderer::Draw() {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SingleTriangleRenderer::ReadyToShutdown () {
    glDeleteProgram(m_shaderProgramId);
    glDeleteBuffers(1, &m_vertexPositionBufferObjectId);
    glDeleteBuffers(1, &m_vertexColorBufferObjectId);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}
