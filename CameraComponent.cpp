#include "CameraComponent.h"
#include <random>

extern GLFWwindow* window;
extern glm::mat4 currentMatrix;

float rotationIncrement;
const float CAMERA_SHAKE_INTENSITY = 0.025f;

std::default_random_engine cameraShakeGenerator;
std::uniform_real_distribution<float> cameraShakeDistribution(-1.0f, 1.0f);

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

    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float offsetZ = 0.0f;

    if (cameraShakeTime > 0.0f)
    {
        offsetX = cameraShakeDistribution(cameraShakeGenerator) * CAMERA_SHAKE_INTENSITY;
        offsetY = cameraShakeDistribution(cameraShakeGenerator) * CAMERA_SHAKE_INTENSITY;
    }

    view = glm::rotate(view, gameObject->rotation.x + offsetX, glm::vec3(1, 0, 0));
    view = glm::rotate(view, gameObject->rotation.y + offsetY, glm::vec3(0, 1, 0));
    view = glm::translate(view, -gameObject->position);

    currentMatrix = view;

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

    if (cameraShakeTime > 0.0f)
    {
        cameraShakeTime -= elapsedTime;
    }
}

void CameraComponent::lookLeft()
{
    gameObject->rotation.y -= rotationIncrement;
}

void CameraComponent::lookRight()
{
    gameObject->rotation.y += rotationIncrement;
}
