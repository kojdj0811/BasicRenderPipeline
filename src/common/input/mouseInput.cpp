#include "mouseInput.h"


MouseInput::MouseInput()
{
    leftButton = new MouseButton();
    middleButton = new MouseButton();
    rightButton = new MouseButton();
}

MouseInput::~MouseInput()
{
    delete leftButton;
    delete middleButton;
    delete rightButton;
}

void MouseInput::UpdateCurrentMouseButtonState (GLFWwindow* window, int action, MouseButton* target) {
    switch (action)
    {
        case GLFW_PRESS: {
            target->SetDrag(true);
            target->UpdateDragStartPosition(window);
            break;
        }
        
        case GLFW_RELEASE: {
            target->SetDrag(false);
            target->UpdateDragEndPosition(window);
            break;
        }
        
        default:
            break;
    }
}


glm::vec2 MouseInput::GetScreenPosition() {
    return m_screenPosition;
}

glm::vec2 MouseInput::GetScreenDeltaPosition() {
    return m_screenDeltaPosition;
}

glm::vec2 MouseInput::GetDeltaWheel() {
    return m_deltaWheel;
}


void MouseInput::UpdateScreenPosition (GLFWwindow* window) {
    glm::vec2 previousPosition = m_screenPosition;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    m_screenPosition = glm::vec2(xpos, ypos);

    m_screenDeltaPosition = m_screenPosition - previousPosition;
}


void MouseInput::UpdateDeltaWheel (GLFWwindow* window) {
    // double xpos, ypos;
    // glfwGetCursorPos(window, &xpos, &ypos);
    // m_deltaWheel = glm::vec2(xpos, ypos);
}
