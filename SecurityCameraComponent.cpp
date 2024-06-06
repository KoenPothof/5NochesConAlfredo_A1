#include "SecurityCameraComponent.h"

SecurityCameraComponent::SecurityCameraComponent(int id, int x, int y, int width, int height, const glm::vec3& pos, const glm::vec3& rot)
    : id(id), viewportX(x), viewportY(y), viewportWidth(width), viewportHeight(height), position(pos), rotation(rot)
{
}

SecurityCameraComponent::~SecurityCameraComponent()
{
}