#pragma once
#include <memory>
#include <GL/glew.h>
#include "tigl.h"
#include <GLFW/glfw3.h>
#include "cmath"
#include <iostream>
#include <string>
#include "LightComponent.h"

class GameObject;

class GameManager
{

public:
	unsigned int usage = 1;
	float countdown = 100.0f;
	float timeline = 12.0f;
	float deltaTime;
	std::shared_ptr<GameObject> lighting;
	std::shared_ptr<GameObject> enemy;
	std::shared_ptr<GameObject> enemy1, enemy2, enemy3, runningEnemy;
	std::shared_ptr<GameObject> leftDoor;
	std::shared_ptr<GameObject> rightDoor;
	std::shared_ptr<GameObject> player;
	std::shared_ptr<GameObject> cameraSystemToggler;
	bool gameOver = false;
	bool gameWon = false;
	bool jumpscareFinished = false;

	enum Sounds
	{
		DOOR_OPEN,
		DOOR_CLOSE,
		LOSE,
		WIN,
		BEWEEGBEEST,
		JUMPSCARE,
		CAMERA,
		BEGIN,
		RUNNING
	};
	GameManager();
	~GameManager();
	void update(float elapsedTime);
	void init();
	void reset();
	void gameOverScript(float elapsedTime);
	void gameWonScript(float elapsedTime);
	void setGameWon();
	bool isGameOver();
	bool isGameWon();
	bool rightDoorClosed();
	bool leftDoorClosed();
	void rightDoorToggle();
	void leftDoorToggle();
	void playSound(Sounds sound);
	void toggleCameraSystem();
	bool cameraSystemIsOff();
	void powerSystem();
};

