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

	enum Sounds
	{
		DOOR_OPEN,
		DOOR_CLOSE,
		LOSE,
		WIN
	};

public:
	unsigned int usage = 1;
	float countdown = 100.0f;
	float timeline = 12.0f;
	float deltaTime;
	std::shared_ptr<GameObject> enemy;
	std::shared_ptr<GameObject> leftDoor;
	std::shared_ptr<GameObject> rightDoor;
	std::shared_ptr<GameObject> player;
	bool gameOver = false;
	bool gameWon = false;
	bool jumpscareFinished = false;
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
};

