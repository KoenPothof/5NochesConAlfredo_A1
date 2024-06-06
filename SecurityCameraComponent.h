#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "Component.h"

class SecurityCameraComponent : public Component
{
public:
    int id;
    int viewportX, viewportY, viewportWidth, viewportHeight;
    glm::vec3 position;
    glm::vec3 rotation;

    SecurityCameraComponent(int id, int x, int y, int width, int height, const glm::vec3& pos, const glm::vec3& rot);
    ~SecurityCameraComponent(); // Destructor declaration
};

