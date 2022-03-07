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
    shaderProgram->setVertexShader("src/shaders/simpleVertexShader.glsl");
    shaderProgram->setFragmentShader("src/shaders/simpleFragmentShader.glsl");
    shaderProgramId = shaderProgram->compile();

    //setup quad data
    glGenBuffers(1, &vertexPositionBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);

    glGenBuffers(1, &vertexColorBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexColorBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);

    //use activate
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //element buffer
    GLuint elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer), indexBuffer, GL_STATIC_DRAW);




    GLuint positionAttribute = shaderProgram->getAttribLocation("positionAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBufferObjectId);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    GLuint colorAttribute = shaderProgram->getAttribLocation("colorAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, vertexColorBufferObjectId);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttribute);

    GLuint mvpUniform = shaderProgram->getUniformLocation("MVP");
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    glBindVertexArray(0);



    shaderProgram->use();
    glBindVertexArray(vertexArrayObject);
}

void SingleQuadRenderer::Update (float a_deltaTime) {
    GLuint mvpUniform = shaderProgram->getUniformLocation("MVP");
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &m_mvpMatrix[0][0]);
}

void SingleQuadRenderer::Draw() {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SingleQuadRenderer::ReadyToShutdown () {
    glDeleteProgram(shaderProgramId);
    glDeleteBuffers(1, &vertexPositionBufferObjectId);
    glDeleteBuffers(1, &vertexColorBufferObjectId);
    glDeleteVertexArrays(1, &vertexArrayObject);
}
