#include "DebugComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include "GameObject.h"

extern GLFWwindow* window;

const float speed = 6.0f;

DebugComponent::DebugComponent()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void DebugComponent::move(float angle, float elapsedTime)
{
    gameObject->position.x += (float)cos(gameObject->rotation.y + glm::radians(angle)) * speed * elapsedTime;
    gameObject->position.z += (float)sin(gameObject->rotation.y + glm::radians(angle)) * speed * elapsedTime;
}

void DebugComponent::update(float elapsedTime)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    static double lastX = x;
    static double lastY = y;

    gameObject->rotation.x -= (float)(lastY - y) / 100.0f;
    gameObject->rotation.y -= (float)(lastX - x) / 100.0f;

    lastX = x;
    lastY = y;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        move(0, elapsedTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        move(180, elapsedTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        move(90, elapsedTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        move(-90, elapsedTime);
}

void DebugComponent::handleInput(float deltaTime)
{
    //float velocity = cameraSpeed * deltaTime;

    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //    cameraPosition += cameraDirection * velocity;
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    cameraPosition -= cameraDirection * velocity;
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    cameraPosition -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * velocity;
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    cameraPosition += glm::normalize(glm::cross(cameraDirection, cameraUp)) * velocity;

    //// Handle up and down movement
    //if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    //    cameraPosition += cameraUp * velocity;
    //if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    //    cameraPosition -= cameraUp * velocity;
}