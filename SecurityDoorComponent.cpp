#include "SecurityDoorComponent.h"
#include "GameObject.h"

const float DOOR_OPEN_Y = 5.850f;
const float DOOR_CLOSE_Y = 0.0f;

SecurityDoorComponent::SecurityDoorComponent()
{
}

SecurityDoorComponent::~SecurityDoorComponent()
{
}

void SecurityDoorComponent::update(float elapsedTime)
{
	if (isClosed)
	{
		closeDoor(elapsedTime);
	}
	else
	{
		openDoor(elapsedTime);
	}
}

void SecurityDoorComponent::openDoor(float elapsedTime)
{
	if ((gameObject->position.y >= DOOR_OPEN_Y)) return;
	
	else
	{
		gameObject->position.y += 3.0f * elapsedTime;
	} 
}

void SecurityDoorComponent::closeDoor(float elapsedTime)
{
	if ((gameObject->position.y <= DOOR_CLOSE_Y)) return;

	else
	{
		gameObject->position.y -= 3.0f * elapsedTime;
	}
}
