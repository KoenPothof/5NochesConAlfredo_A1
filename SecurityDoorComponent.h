#pragma once
#include "Component.h"
class SecurityDoorComponent : public Component
{
public:
	bool isClosed = false;
	SecurityDoorComponent();
	~SecurityDoorComponent();
	void update(float elapsedTime) override;
	void openDoor();
	void closeDoor();
};

