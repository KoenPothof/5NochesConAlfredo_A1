#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"
#include "GameObject.h"

class CameraComponent : public Component {
public:
    CameraComponent(float rotationSpeed, float moveSpeed);
    ~CameraComponent();

    glm::mat4 getMatrix() const;
    void move(float angle, float fac);
    virtual void update(float elapsedTime) override;

private:
    glm::vec3 position;
    glm::vec2 rotation;
    float rotationSpeed;
    float moveSpeed;
};
