#include "utility.h"

Utility* Utility::m_instance;


Utility::Utility()
{
    triangleShaderProgram = new Shader();
}

Utility::~Utility()
{
    if(m_instance != nullptr)
        delete m_instance;
}


Utility* Utility::GetInstance () {
    if(m_instance == nullptr) {
        m_instance = new Utility();
    }

    return m_instance;
}


void Utility::SetupRenderingData_SingleTriangle () {
    //define shader
    triangleShaderProgram->setVertexShader("src/shaders/simpleVertexShader.glsl");
    triangleShaderProgram->setFragmentShader("src/shaders/simpleFragmentShader.glsl");
    triangleShaderProgramId = triangleShaderProgram->compile();

    //setup triangle data
    glGenBuffers(1, &triangleVertexPositionBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexPositionBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_position), triangle_position, GL_STATIC_DRAW);

    glGenBuffers(1, &triangleVertexColorBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexColorBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_color), triangle_color, GL_STATIC_DRAW);

    //use activate
    glGenVertexArrays(1, &triangleVertexArrayObject);
    glBindVertexArray(triangleVertexArrayObject);


    GLuint positionAttribute = glGetAttribLocation(triangleShaderProgramId, "positionAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexPositionBufferObjectId);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    GLuint colorAttribute = glGetAttribLocation(triangleShaderProgramId, "colorAttribute");
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexColorBufferObjectId);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorAttribute);

    glBindVertexArray(0);



    triangleShaderProgram->use();
    glBindVertexArray(triangleVertexArrayObject);
}

void Utility::ReadyToShutdown_SingleTriangle () {
    glDeleteProgram(triangleShaderProgramId);
    glDeleteBuffers(1, &triangleVertexPositionBufferObjectId);
    glDeleteBuffers(1, &triangleVertexColorBufferObjectId);
    glDeleteVertexArrays(1, &triangleVertexArrayObject);
}

std::string Utility::ReadStringFromFile (char* filePath) {
    std::ifstream ifs(filePath);
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();

    std::string buffer(size, ' ');
    ifs.seekg(0);
    ifs.read(&buffer[0], size);

    ifs.close();

    return buffer;
}
