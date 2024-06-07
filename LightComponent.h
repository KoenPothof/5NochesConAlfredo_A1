#pragma once
#include "Component.h"
#include "tigl.h"

class LightComponent : public Component
{
private:
	unsigned int lightIndex;
public:
	glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
	bool directional = false;

	LightComponent();
	~LightComponent();
	virtual void update(float elapsedTime) override;
};

