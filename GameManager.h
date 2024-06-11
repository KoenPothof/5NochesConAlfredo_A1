#pragma once
#include <memory>
#include <GL/glew.h>
#include "tigl.h"
#include <GLFW/glfw3.h>
#include "cmath"
#include <iostream>
#include <string>

class GameObject;

class GameManager
{

private:

	/*enum Sounds
	{
		DOOR_OPEN,
		DOOR_CLOSE,
		LOSE,
		WIN,
		BEWEEGBEEST,
		JUMPSCARE,
		BEGIN
	};*/

	
public:
	unsigned int usage = 1;
	float countdown = 100.0f;
	float timeline = 12.0f;
	float deltaTime;
	std::shared_ptr<GameObject> enemy1, enemy2, enemy3;
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
		CAMERA
		JUMPSCARE,
		BEGIN
	};
	GameManager();
	~GameManager();
	void update(float elapsedTime);
	void init();
	void reset();
	void gameOverScript(float elapsedTime);
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
};

