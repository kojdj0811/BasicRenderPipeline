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
    shaderProgram->setVertexShader("src/shaders/simpleVertexShader.glsl");
    shaderProgram->setFragmentShader("src/shaders/simpleFragmentShader.glsl");
    shaderProgramId = shaderProgram->compile();

    //setup triangle data
    glGenBuffers(1, &vertexPositionBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);

    glGenBuffers(1, &vertexColorBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexColorBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);

    //use activate
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    GLuint positionAttribute = glGetAttribLocation(shaderProgramId, "positionAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBufferObjectId);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    GLuint colorAttribute = glGetAttribLocation(shaderProgramId, "colorAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, vertexColorBufferObjectId);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttribute);

    glBindVertexArray(0);



    shaderProgram->use();
    glBindVertexArray(vertexArrayObject);
}

void SingleTriangleRenderer::Update(float a_deltaTime) {
}

void SingleTriangleRenderer::Draw() {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SingleTriangleRenderer::ReadyToShutdown () {
    glDeleteProgram(shaderProgramId);
    glDeleteBuffers(1, &vertexPositionBufferObjectId);
    glDeleteBuffers(1, &vertexColorBufferObjectId);
    glDeleteVertexArrays(1, &vertexArrayObject);
}
