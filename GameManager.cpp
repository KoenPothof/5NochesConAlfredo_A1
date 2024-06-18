#include "GameManager.h"
#include "GameObject.h"
#include "SecurityDoorComponent.h"
#include "CameraSystemToggleComponent.h"
#include <iostream>
#include <string>
#include "TextComponent.h"
#include "EnemyComponent.h"
#include "DoubleTextComponent.h"
#include "EnemyComponent.h"
#include <string>
#include <irrKlang.h>
#include "CameraComponent.h"
#include "RunningEnemyComponent.h"
#include "MusicEnemyComponent.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace std;

extern int selectedCamera;

float passedTime = glfwGetTime();
float drainSpeed = 0.14f;
bool powerLeft = true;
bool played = true;
bool played1 = true;
bool played2 = true;

string camera;

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
	if (gameOver)
	{
		gameOverScript(elapsedTime);
		return;
	}

	if (gameWon)
	{
		gameWonScript(elapsedTime);
		return;
	}

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

	countdown -= elapsedTime * drainSpeed * ((float)usage * 0.85f);


	if (passedTime < 70.0f){
		timeline = 12;
		if (played) {
			played = false;
			playSound(BEGIN);
		}
	}
	else if (passedTime < 160.0f && passedTime > 100.0f) {
		timeline = 1;
	}
	else if (passedTime < 220.0f && passedTime > 160.0f) {
		timeline = 2;
		//enemy1->getComponent<EnemyComponent>()->isFrozen = false;
		if (played1) {
			played1 = false;
			playSound(twoAM);
		}
		//enemy1->getComponent<EnemyComponent>()->isFrozen = false;
		musicEnemy->getComponent<MusicEnemyComponent>()->isFrozen = false;
	}
	else if (passedTime < 280.0f && passedTime > 220.0f) {
		timeline = 3;
	}
	else if (passedTime < 340.0f && passedTime > 280.0f) {
		timeline = 4;
		if (played2) {
			played2 = false;
			playSound(fourAM);
		}
		runningEnemy->getComponent<RunningEnemyComponent>()->isFrozen = false;
	}
	else if (passedTime < 400.0f && passedTime > 340.0f) {
		timeline = 5;
	}
	else if (passedTime < 460.0f && passedTime > 400.0f) {
		timeline = 6;
		gameWon = true;
	}
	else {
		passedTime = 0.0f;
	}

	if (selectedCamera == 1) {
		camera = "B";
	}
	else if (selectedCamera == 2) {
		camera = "C";
	}
	else if (selectedCamera == 3) {
		camera = "D";
	}
	else if (selectedCamera == 4) {
		camera = "E";
	}
	else if (selectedCamera == 5) {
		camera = "F";
	}
	else if (selectedCamera == 6) {
		camera = "G";
	}
	else if (selectedCamera == 7) {
		camera = "H";
	}
	else if (selectedCamera == 8) {
		camera = "I";
	}
	else if (selectedCamera == 9) {
		camera = "J";
	}
	else if (selectedCamera == 10) {
		camera = "K";
	}

	player->getComponent<DoubleTextComponent>()->text3->text = "Room " + camera;

	player->getComponent<DoubleTextComponent>()->text1->text = "Power: " + round_to_string(countdown, 1) + "%";

	if (timeline == 12) {
		player->getComponent<DoubleTextComponent>()->text2->text = round_to_string(timeline, 0) + "PM";
	}
	else {
		player->getComponent<DoubleTextComponent>()->text2->text = round_to_string(timeline, 0) + "AM";
	}
	
	tigl::shader->enableLighting(true);
	powerSystem();
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
	tigl::shader->enableLighting(false);
	enemy1->getComponent<EnemyComponent>()->isFrozen = true;
	enemy2->getComponent<EnemyComponent>()->isFrozen = true;
	enemy3->getComponent<EnemyComponent>()->isFrozen = true;
	runningEnemy->getComponent<RunningEnemyComponent>()->isFrozen = true;
	musicEnemy->getComponent<MusicEnemyComponent>()->isFrozen = true;

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

void GameManager::gameWonScript(float elapsedTime)
{
	tigl::shader->enableLighting(false);
	static int played = 1;
	enemy1->getComponent<EnemyComponent>()->isFrozen = true;
	enemy2->getComponent<EnemyComponent>()->isFrozen = true;
	enemy3->getComponent<EnemyComponent>()->isFrozen = true;
	runningEnemy->getComponent<RunningEnemyComponent>()->isFrozen = true;



	musicEnemy->getComponent<MusicEnemyComponent>()->isFrozen = true;

	if (true)
	{

		if (played == 1)
		{
			playSound(WIN);
			played++;
		}
		player->position = glm::vec3(-23.211f, 2, -57.633f); // Teleport player to game over room
		player->rotation = glm::vec3(0, 0, 0);
	}
	else
	{
		
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
	if (!powerLeft) { return; }

	rightDoor->getComponent<SecurityDoorComponent>()->isClosed = !rightDoor->getComponent<SecurityDoorComponent>()->isClosed;
	if (rightDoor->getComponent<SecurityDoorComponent>()->isClosed)
		playSound(DOOR_CLOSE);
	else
		playSound(DOOR_OPEN);
}

void GameManager::leftDoorToggle()
{
	if (!powerLeft) { return; }

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
			soundPlay = soundEngine->play2D("assets/sounds/musicWin(1).mp3", false, false, true);
			break;

		case BEWEEGBEEST:
			soundPlay = soundEngine->play2D("assets/sounds/footstepMetal.mp3", false, false, true);
			break;
		
		case JUMPSCARE:
			soundPlay = soundEngine->play2D("assets/sounds/jumpscare.mp3", false, false, true);
			break;
		case CAMERA:
			soundPlay = soundEngine->play2D("assets/sounds/cameraSound.mp3", false, false, true);
			break;
		case CRASH:
			soundPlay = soundEngine->play2D("assets/sounds/crash_sound.mp3", false, false, true);
			break;
		case BEGIN:
			soundPlay = soundEngine->play2D("assets/sounds/introclip2.0.mp3", false, false, true);
			break;
		case RUNNING:
			soundPlay = soundEngine->play2D("assets/sounds/running_sounds.mp3", false, false, true);
			break;
		case twoAM:
			soundPlay = soundEngine->play2D("assets/sounds/2uurClip.mp3", false, false, true);
			break;
		case fourAM:
			soundPlay = soundEngine->play2D("assets/sounds/4uurClip.mp3", false, false, true);
			break;
	}
}

void GameManager::toggleCameraSystem()
{
	if (!powerLeft) { return; }

	cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isOff = !cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isOff;
	if (cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isOff)
		playSound(CAMERA);

}

bool GameManager::cameraSystemIsOff()
{
	return cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isSystemOff();
}

void GameManager::powerSystem()
{

	if (countdown < 0.0) {
		if (!cameraSystemIsOff()) {
			toggleCameraSystem();
		}
		if (rightDoorClosed()) {
			rightDoorToggle();
		}
		if (leftDoorClosed()) {
			leftDoorToggle();
		}
		
		powerLeft = false;

		lighting->getComponent<LightComponent>()->ambient.x = 0.3;
		lighting->getComponent<LightComponent>()->ambient.y = 0.3;
		lighting->getComponent<LightComponent>()->ambient.z = 0.3;

	}
	else {
		powerLeft = true;
	}

}
