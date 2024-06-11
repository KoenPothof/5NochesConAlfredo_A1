#include "CameraSystemToggleComponent.h"
#include "GameObject.h"

const float RECTANGLE_UP_Y = 20.0f;
const float RECTANGLE_DOWN_Y = 0.0f;

CameraSystemToggleComponent::CameraSystemToggleComponent()
{
}

CameraSystemToggleComponent::~CameraSystemToggleComponent()
{
}

void CameraSystemToggleComponent::update(float elapsedTime)
{
	if (isOff)
	{
		systemOff();
	}
	else
	{
		systemOn();
	}
}

void CameraSystemToggleComponent::systemOn()
{
	gameObject->position.y = RECTANGLE_UP_Y;
}

void CameraSystemToggleComponent::systemOff()
{
	gameObject->position.y = RECTANGLE_DOWN_Y;
}

bool CameraSystemToggleComponent::isSystemOff()
{
	return isOff;
}