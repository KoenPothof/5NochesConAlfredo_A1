#include "CameraComponent.h"
extern GLFWwindow* window;

float rotationIncrement;

CameraComponent::CameraComponent(float rotationSpeed, float moveSpeed)
    : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f), rotationSpeed(rotationSpeed), moveSpeed(moveSpeed)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

CameraComponent::CameraComponent(const CameraComponent& obj)
{
	
}

CameraComponent::~CameraComponent()
{
}

glm::mat4 CameraComponent::getMatrix() const
{
    glm::mat4 view(1.0f);
    view = glm::rotate(view, gameObject->rotation.x, glm::vec3(1, 0, 0));
    view = glm::rotate(view, gameObject->rotation.y, glm::vec3(0, 1, 0));
    view = glm::translate(view, -gameObject->position);
    return view;
}

void CameraComponent::move(float angle, float fac)
{
    glm::vec3 direction(cos(gameObject->rotation.y + glm::radians(angle)), 0.0f, sin(gameObject->rotation.y + glm::radians(angle)));
    gameObject->position += direction * fac;
}

void CameraComponent::update(float elapsedTime)
{
    const float rotationSpeed = 0.3f;
	const float moveSpeed = 5.0f;
    
    rotationIncrement = rotationSpeed * elapsedTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        gameObject->rotation.y -= rotationIncrement;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        gameObject->rotation.y += rotationIncrement;
}

void CameraComponent::lookLeft()
{
    gameObject->rotation.y -= rotationIncrement;
}

void CameraComponent::lookRight()
{
    gameObject->rotation.y += rotationIncrement;
}
