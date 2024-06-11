#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include <iostream>
#include <string>
#include "TextComponent.h"
#include "DoubleTextComponent.h"
#include "EnemyComponent.h"
#include <irrKlang.h>
#include "CameraComponent.h"

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
	if (gameOver)
	{
		gameOverScript(elapsedTime);
		return;
	}

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


	if (deltaTime > 60.0f){
		timeline = 12;
	}
	else if (deltaTime < 120.0f && deltaTime > 60.0f) {
		timeline = 1;
	}
	else if (deltaTime < 180.0f && deltaTime > 120.0f) {
		timeline = 2;
	}
	else if (deltaTime < 240.0f && deltaTime > 180.0f) {
		timeline = 3;
	}
	else if (deltaTime < 300.0f && deltaTime > 240.0f) {
		timeline = 4;
	}
	else if (deltaTime < 360.0f && deltaTime > 300.0f) {
		timeline = 5;
	}
	else if (deltaTime < 420.0f && deltaTime > 360.0f) {
		timeline = 6;
	}


	player->getComponent<DoubleTextComponent>()->text1->text = "Power: " + std::to_string(countdown) + "%";


	if (timeline == 12)
		player->getComponent<DoubleTextComponent>()->text2->text = std::to_string(timeline) + "PM";

	if(timeline > 12)
		player->getComponent<DoubleTextComponent>()->text2->text = std::to_string(timeline) + "AM";
}


void GameManager::init()
{
	soundEngine = irrklang::createIrrKlangDevice();
}

void GameManager::reset()
{
}

void GameManager::gameOverScript(float elapsedTime)
{
	enemy->getComponent<EnemyComponent>()->isFrozen = true;

	if (player->getComponent<CameraComponent>()->cameraShakeTime >= 0.0f)
	{
		player->getComponent<CameraComponent>()->update(elapsedTime);
	}
	else
	{
		player->position = glm::vec3(-23.211f, 2, -7.633f); // Teleport player to game over room
		player->rotation = glm::vec3(0, 0, 0);
	}
	
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
