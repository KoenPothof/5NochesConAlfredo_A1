#pragma once
#include "Component.h"
class CameraSystemToggleComponent : public Component
{
public:
	bool isOff = true;
	CameraSystemToggleComponent();
	~CameraSystemToggleComponent();
	void update(float elapsedTime) override;
	void systemOn();
	void systemOff();
	bool isSystemOff();
};