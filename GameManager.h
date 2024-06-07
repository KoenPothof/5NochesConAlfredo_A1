#pragma once
#include <memory>
#include "tigl.h"
#include <GLFW/glfw3.h>

class GameObject;

class GameManager
{
public:
	unsigned int usage = 1;
	float countdown = 100.0f;
	float elapsedTime;
	float deltaTime;
	std::shared_ptr<GameObject> enemy;
	std::shared_ptr<GameObject> leftDoor;
	std::shared_ptr<GameObject> rightDoor;
	std::shared_ptr<GameObject> player;
	bool gameOver = false;
	bool gameWon = false;
	GameManager();
	~GameManager();
	void update(float elapsedTime);
	void init();
	void reset();
	void setGameOver();
	void setGameWon();
	bool isGameOver();
	bool isGameWon();
	bool rightDoorClosed();
	bool leftDoorClosed();
};

