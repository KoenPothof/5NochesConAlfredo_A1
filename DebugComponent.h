#ifndef DEBUGCOMPONENT_H
#define DEBUGCOMPONENT_H

#include "Component.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class DebugComponent : public Component
{
private:
    GLFWwindow* window;
    glm::vec3 cameraPosition;
    glm::vec3 cameraDirection;
    glm::vec3 cameraUp;
    float cameraSpeed;

public:
    DebugComponent(GLFWwindow* window);
    virtual void update(float deltaTime) override;
    void handleInput(float deltaTime);
};

#endif