#pragma once

#include <iostream>
#include <fstream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class MouseButton;

class MouseInput
{
private:
    glm::vec2 m_screenPosition;
    glm::vec2 m_screenDeltaPosition;
    glm::vec2 m_deltaWheel;


public:
    MouseButton* leftButton;
    MouseButton* middleButton;
    MouseButton* rightButton;


private:

public:
    MouseInput();
    ~MouseInput();

    void UpdateCurrentMouseButtonState (GLFWwindow* window, int action, MouseButton* target);

    glm::vec2 GetScreenPosition();
    glm::vec2 GetScreenDeltaPosition();
    glm::vec2 GetDeltaWheel();

    void UpdateScreenPosition(GLFWwindow* window);
    void UpdateDeltaWheel(GLFWwindow* window);
};


class MouseButton {
private:
    bool m_isDrag = false;
    glm::vec2 m_dragStartPosition;
    glm::vec2 m_dragEndPosition;

public:

private:

public:


    bool IsDrag() { return m_isDrag; }
    void SetDrag(bool active) { m_isDrag = active; }

    glm::vec2 GetDragStartPosition() { return m_dragStartPosition; }
    void UpdateDragStartPosition(GLFWwindow* window) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        m_dragStartPosition = glm::vec2(xpos, ypos);
    }

    glm::vec2 GetDragEndPosition() { return m_dragEndPosition; }
    void UpdateDragEndPosition(GLFWwindow* window) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        m_dragStartPosition = glm::vec2(xpos, ypos);
    }
};