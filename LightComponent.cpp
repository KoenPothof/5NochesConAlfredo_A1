#include "LightComponent.h"
#include "GameObject.h"

static unsigned int lightCount = 0;

LightComponent::LightComponent()
{
	lightIndex = lightCount;
	lightCount++;
	tigl::shader->setLightCount(lightCount);
}

LightComponent::~LightComponent()
{
}

void LightComponent::update(float elapsedTime)
{
	tigl::shader->enableLighting(true);
	tigl::shader->setLightPosition(lightIndex, gameObject->position);
	tigl::shader->setLightAmbient(lightIndex, ambient);
	tigl::shader->setLightDiffuse(lightIndex, diffuse);
	tigl::shader->setLightSpecular(lightIndex, specular);
	tigl::shader->setLightDirectional(lightIndex, directional);
}