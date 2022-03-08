#include "singleQuadRenderer.h"



SingleQuadRenderer::SingleQuadRenderer(glm::mat4 mvpMatrix) : BasicRendererEntity(mvpMatrix)
{
    if (m_vertexBuffer != nullptr ||
        m_vertexColorBuffer != nullptr ||
        m_indexBuffer != nullptr)
        return;

    m_vertexBuffer = new GLfloat[12] {
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    m_vertexColorBuffer = new GLfloat[12] {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    m_indexBuffer = new GLuint[6] {
        0, 1, 3,
        3, 1, 2
    };
}



void SingleQuadRenderer::SetupRenderingData () {
    //define shader
    m_shaderProgram->setVertexShader("src/shaders/simpleVertexShader.glsl");
    m_shaderProgram->setFragmentShader("src/shaders/simpleFragmentShader.glsl");
    m_shaderProgramId = m_shaderProgram->compile();

    //setup quad data
    glGenBuffers(1, &m_vertexPositionBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);

    glGenBuffers(1, &m_vertexColorBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexColorBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);

    //use activate
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    //element buffer
    GLuint elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer), indexBuffer, GL_STATIC_DRAW);




    GLuint positionAttribute = m_shaderProgram->getAttribLocation("positionAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBufferObjectId);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    GLuint colorAttribute = m_shaderProgram->getAttribLocation("colorAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexColorBufferObjectId);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttribute);

    GLuint mvpUniform = m_shaderProgram->getUniformLocation("MVP");
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    glBindVertexArray(0);



    m_shaderProgram->use();
    glBindVertexArray(m_vertexArrayObject);
}

void SingleQuadRenderer::Update (float a_deltaTime) {
    GLuint mvpUniform = m_shaderProgram->getUniformLocation("MVP");
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &m_mvpMatrix[0][0]);
}

void SingleQuadRenderer::Draw() {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SingleQuadRenderer::ReadyToShutdown () {
    glDeleteProgram(m_shaderProgramId);
    glDeleteBuffers(1, &m_vertexPositionBufferObjectId);
    glDeleteBuffers(1, &m_vertexColorBufferObjectId);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}
