#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;

float passedTime = glfwGetTime();


GameManager::GameManager() :countdown(100), elapsedTime(0.0f), passedTime(0.0f)
{
	
}

GameManager::~GameManager()
{
}

void GameManager::update(float elapsedTime)
{
    float currentTime = glfwGetTime();
    deltaTime = currentTime - passedTime;
    passedTime = currentTime;

    elapsedTime += deltaTime;
	cout << elapsedTime << endl;

    if (elapsedTime >= 1.0f) {
        countdown -= elapsedTime/5;
        elapsedTime = 0.0f;

        if (countdown < 0) {
            countdown = 0;
        }
    }
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
