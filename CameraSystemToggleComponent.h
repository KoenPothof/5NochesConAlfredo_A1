#pragma once
#include "Component.h"
class CameraSystemToggleComponent : public Component
{
public:
	bool isOff = false;
	CameraSystemToggleComponent();
	~CameraSystemToggleComponent();
	void update(float elapsedTime) override;
	void systemOn();
	void systemOff();
	bool isSystemOff();
};