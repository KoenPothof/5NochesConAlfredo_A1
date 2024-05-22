#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"

class CameraComponent : public Component {
public:
    CameraComponent(GLFWwindow* window, float rotationSpeed = 1.0f, float moveSpeed = 5.0f);
    ~CameraComponent();

    glm::mat4 getMatrix() const;
    void move(float angle, float fac);
    void update(float elapsedTime) override;

private:
    GLFWwindow* window;  
    glm::vec3 position;
    glm::vec2 rotation;
    float rotationSpeed;
    float moveSpeed;
};