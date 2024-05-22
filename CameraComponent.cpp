#include "CameraComponent.h"

CameraComponent::CameraComponent(GLFWwindow* window, float rotationSpeed, float moveSpeed)
    : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f), rotationSpeed(rotationSpeed), moveSpeed(moveSpeed)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

CameraComponent::~CameraComponent()
{
}

glm::mat4 CameraComponent::getMatrix() const
{
    glm::mat4 view(1.0f);
    view = glm::rotate(view, rotation.x, glm::vec3(1, 0, 0));
    view = glm::rotate(view, rotation.y, glm::vec3(0, 1, 0));
    view = glm::translate(view, -position);
    return view;
}

void CameraComponent::move(float angle, float fac)
{
    glm::vec3 direction(cos(rotation.y + glm::radians(angle)), 0.0f, sin(rotation.y + glm::radians(angle)));
    position += direction * fac;
}

void CameraComponent::update(GLFWwindow* window)
{
    static const float rotationSpeed = 1.0f;
    double currentFrameTime = glfwGetTime();
    static double lastFrameTime = currentFrameTime;
    float deltaTime = static_cast<float>(currentFrameTime - lastFrameTime);
    lastFrameTime = currentFrameTime;

    float rotationIncrement = rotationSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotation.y -= rotationIncrement;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotation.y += rotationIncrement;

    float moveIncrement = moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        move(0, moveIncrement);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        move(180, moveIncrement);
}
