#include "DebugComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"

DebugComponent::DebugComponent(GLFWwindow* window)
    : window(window), cameraPosition(glm::vec3(0, 10, 10)), cameraDirection(glm::vec3(0, -1, -1)), cameraUp(glm::vec3(0, 1, 0)), cameraSpeed(5.0f)
{
}

void DebugComponent::update(float deltaTime)
{
    handleInput(deltaTime);

    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
    tigl::shader->setViewMatrix(view);
}

void DebugComponent::handleInput(float deltaTime)
{
    float velocity = cameraSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraDirection * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraDirection * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraDirection, cameraUp)) * velocity;

    // Handle up and down movement
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPosition += cameraUp * velocity;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPosition -= cameraUp * velocity;
}