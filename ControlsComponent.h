#pragma once
#include "Component.h"
#include "CameraComponent.h"

class ControlsComponent : public Component
{
	private:

	public:

	enum CONTROLS
	{
		DOORLEFT,
		DOORRIGHT,
		LOOKLEFT,
		LOOKRIGHT,
		CAMERASWITCH,
		TOGGLECAMERAS
	};

	ControlsComponent();
	~ControlsComponent();
	void controls(CONTROLS control);
};

