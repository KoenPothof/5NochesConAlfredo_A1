#ifndef DEBUGCOMPONENT_H
#define DEBUGCOMPONENT_H

#include "Component.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class DebugComponent : public Component
{
private:
    float cameraSpeed;

public:
    DebugComponent();
    virtual void update(float deltaTime) override;
    void handleInput(float deltaTime);
    void move(float, float);
};

#endif