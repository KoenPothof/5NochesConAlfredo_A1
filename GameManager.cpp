#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include "GLFW/glfw3.h"


float passedTime = glfwGetTime();


GameManager::GameManager()
{
	
}

GameManager::~GameManager()
{
}

void GameManager::update(float elapsedTime)
{
	float currentTime = glfwGetTime();
	deltaTime = float(passedTime - currentTime);
}

void GameManager::init()
{
}

void GameManager::reset()
{
}

void GameManager::setGameOver()
{
}

void GameManager::setGameWon()
{
}

bool GameManager::isGameOver()
{
	return false;
}

bool GameManager::isGameWon()
{
	return false;
}

bool GameManager::rightDoorClosed()
{
	return rightDoor->getComponent<SecurityDoorComponent>()->isClosed;
}

bool GameManager::leftDoorClosed()
{
	return leftDoor->getComponent<SecurityDoorComponent>()->isClosed;
}
