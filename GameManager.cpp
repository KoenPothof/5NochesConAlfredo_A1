#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include "CameraSystemToggleComponent.h"
#include <iostream>
#include <string>
#include "TextComponent.h"
#include "EnemyComponent.h"
#include "DoubleTextComponent.h"
#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace std;

float passedTime = glfwGetTime();
float drainSpeed = 0.25f;

irrklang::ISoundEngine* soundEngine;
irrklang::ISound* soundPlay;

std::string round_to_string(float value, int precision)
{
	return std::to_string(value).substr(0, std::to_string(value).find(".") + precision + 1);
}

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

	cout << passedTime << endl;

	usage = 1;
	if (leftDoorClosed())
		usage++;
	if (rightDoorClosed())
		usage++;
	if (!cameraSystemIsOff())
		usage++;

	countdown -= elapsedTime * drainSpeed * usage;


	if (passedTime < 70.0f){
		timeline = 12;
	}
	else if (passedTime < 130.0f && passedTime > 70.0f) {
		timeline = 1;
	}
	else if (passedTime < 190.0f && passedTime > 130.0f) {
		timeline = 2;
	}
	else if (passedTime < 250.0f && passedTime > 190.0f) {
		timeline = 3;
	}
	else if (passedTime < 310.0f && passedTime > 250.0f) {
		timeline = 4;
	}
	else if (passedTime < 370.0f && passedTime > 310.0f) {
		timeline = 5;
	}
	else if (passedTime < 430.0f && passedTime > 370.0f) {
		timeline = 6;
	}


	player->getComponent<DoubleTextComponent>()->text1->text = "Power: " + round_to_string(countdown, 1) + "%";


	if (timeline == 12) {
		player->getComponent<DoubleTextComponent>()->text2->text = round_to_string(timeline, 0) + "PM";
	}
	else {
		player->getComponent<DoubleTextComponent>()->text2->text = round_to_string(timeline, 0) + "AM";
	}
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

void GameManager::playSound(Sounds sound) 
{

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

		case BEWEEGBEEST:
			soundPlay = soundEngine->play2D("assets/sounds/footstepMetal.mp3", false, false, true);
			break;
		case JUMPSCARE:
			soundPlay = soundEngine->play2D("assets/sounds/jumpscare.mp3", false, false, true);
			break;

	}
}

void GameManager::toggleCameraSystem()
{
	cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isOff = !cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isOff;
}

bool GameManager::cameraSystemIsOff()
{
	return cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isSystemOff();
}
