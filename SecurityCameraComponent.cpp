#include "SecurityCameraComponent.h"

SecurityCameraComponent::SecurityCameraComponent()
{
}

SecurityCameraComponent::~SecurityCameraComponent()
{
}

glm::mat4 SecurityCameraComponent::getCameraMatrix()
{
    glm::mat4 view(1.0f);
    view = glm::rotate(view, camera->rotation.x, glm::vec3(1, 0, 0));
    view = glm::rotate(view, camera->rotation.y, glm::vec3(0, 1, 0));
    view = glm::rotate(view, camera->rotation.z, glm::vec3(0, 0, 1));
    view = glm::translate(view, -camera->position);
    return view;
}