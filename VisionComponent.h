#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "Component.h"

class VisionComponent : public Component
{

	public:
	VisionComponent();
	~VisionComponent();
	void init();
	virtual void update(float elapseTime) override;

	void toggleRightDoor();
	void toggleLeftDoor();

};

