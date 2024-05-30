#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "Component.h"

class SecurityCameraComponent : public Component
{
public:
    std::shared_ptr<GameObject> camera;
    SecurityCameraComponent();
    ~SecurityCameraComponent();
    glm::mat4 getCameraMatrix();
};

