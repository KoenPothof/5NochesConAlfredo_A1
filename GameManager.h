#pragma once
#include <memory>

class GameObject;

class GameManager
{
public:
	std::shared_ptr<GameObject> enemy;
	std::shared_ptr<GameObject> leftDoor;
	std::shared_ptr<GameObject> rightDoor;
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
	void rightDoorToggle();
	void leftDoorToggle();
};

