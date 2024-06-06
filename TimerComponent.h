#pragma once
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

class TimerComponent
{

	public:
	TimerComponent();
	~TimerComponent();

	void Update(float deltaTime);
	void Reset();
	float GetTime();
};



