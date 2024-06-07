#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include <iostream>
#include <string>
#include "TextComponent.h"

using namespace std;

float passedTime = glfwGetTime();
float drainSpeed = 0.25f;


GameManager::GameManager() :elapsedTime(0.0f)
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

	cout << elapsedTime << endl;

	usage = 1;
	if (leftDoorClosed())
		usage++;
	if (rightDoorClosed())
		usage++;

	countdown -= elapsedTime * drainSpeed * usage;
	player->getComponent<TextComponent>()->text = "Battery Level: " + std::to_string(countdown);

    /*if (elapsedTime >= 0.05f) {
        countdown -= elapsedTime/5;
        elapsedTime = 0.0f;

		if (!rightDoorClosed() && !leftDoorClosed()) {
			countdown -= elapsedTime*2;
		}

		if (!rightDoorClosed()) {
			countdown -= elapsedTime/3;
		}
		if (!leftDoorClosed()) {
			countdown -= elapsedTime/3;
		}

		if (countdown == 0) {
		}*/

		// Ensure countdown does not go below 0
		/*if (countdown < 0) {
			countdown = 0;
		}
	}*/
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
