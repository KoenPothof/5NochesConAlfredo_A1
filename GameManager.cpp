#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

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
