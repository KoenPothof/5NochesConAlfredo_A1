#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include <iostream>
#include <string>
#include "TextComponent.h"
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace std;

float passedTime = glfwGetTime();
float drainSpeed = 0.25f;

irrklang::ISoundEngine* soundEngine;
irrklang::ISound* soundPlay;

GameManager::GameManager()
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
	soundEngine = irrklang::createIrrKlangDevice();
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

void GameManager::rightDoorToggle()
{
	rightDoor->getComponent<SecurityDoorComponent>()->isClosed = !rightDoor->getComponent<SecurityDoorComponent>()->isClosed;
	if (rightDoor->getComponent<SecurityDoorComponent>()->isClosed)
		playSound(DOOR_CLOSE);
	else
		playSound(DOOR_OPEN);
}

void GameManager::leftDoorToggle()
{
	leftDoor->getComponent<SecurityDoorComponent>()->isClosed = !leftDoor->getComponent<SecurityDoorComponent>()->isClosed;
	if (leftDoor->getComponent<SecurityDoorComponent>()->isClosed)
		playSound(DOOR_CLOSE);
	else
		playSound(DOOR_OPEN);
}

void GameManager::playSound(Sounds sound) {

	switch (sound)
	{
		case DOOR_OPEN:
			soundPlay = soundEngine->play2D("assets/sounds/doorOpen.mp3", false, false, true);
			break;

		case DOOR_CLOSE:
			soundPlay = soundEngine->play2D("assets/sounds/doorClose.mp3", false, false, true);
			break;

		case WIN:
			soundPlay = soundEngine->play2D("assets/sounds/musicWin.mp3", false, false, true);
			break;
	}
}
