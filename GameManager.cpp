#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include "SoundComponent.h"

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

irrklang::ISoundEngine* soundEngine;
irrklang::ISound* sound;

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
	playSound();
}

void GameManager::leftDoorToggle()
{
	leftDoor->getComponent<SecurityDoorComponent>()->isClosed = !leftDoor->getComponent<SecurityDoorComponent>()->isClosed;
	playSound();
}

void GameManager::playSound() {
	sound = soundEngine->play2D("assets/sounds/musicWin.mp3", true, false, true);
}
