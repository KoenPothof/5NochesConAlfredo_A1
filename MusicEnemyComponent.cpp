#include "MusicEnemyComponent.h"
#include "GameObject.h"
#include "GameManager.h"
#include "CameraComponent.h"
#include <irrKlang.h>

extern irrklang::ISoundEngine* soundEngine;
irrklang::ISound* musicPlay;

MusicEnemyComponent::MusicEnemyComponent()
{
	std::random_device randomDevice;
	generator = std::default_random_engine(randomDevice());
	distribution = std::uniform_int_distribution<int>(1, randomTimeBeforeNextMove);
	positionDistribution = std::uniform_int_distribution<int>(C, B);
	currentLocation = getRandomLocation();
	timeBeforeNextAttack = (float)distribution(generator) + mininumTimeBeforeNextMove;
}

MusicEnemyComponent::~MusicEnemyComponent()
{
}

void MusicEnemyComponent::update(float elapsedTime)
{
	if (isFrozen)
	{
		return;
	}

	timeBeforeNextAttack -= elapsedTime;

	if (timeBeforeNextAttack <= 0.0)
	{
		isPlaying = true;
		move();
	}

	if (isPlaying)
	{
		if (attackTime >= lastAttackTime)
		{
			musicPlay = soundEngine->play2D("assets/sounds/muziekbeest.mp3", false, false, true);
			musicPlay->setVolume(0.5f);
		}
		attackTime -= elapsedTime;
		startPlaying();
		if (canScareAway())
		{
			scareAwayTime -= elapsedTime;
			if (scareAwayTime <= 0.0f)
			{
				stopPlaying();
			}
		}
	}
}

void MusicEnemyComponent::startPlaying()
{
	if (attackTime <= 0.0f)
	{
		jumpscare();
	}
}

bool MusicEnemyComponent::canScareAway()
{
	if (gameObject->gameManager->cameraSystemIsOff())
		return false;

	switch (currentLocation)
	{
	case MusicEnemyComponent::C:
		if (gameObject->gameManager->camera == "C")
			return true;
		break;
	case MusicEnemyComponent::D:
		if (gameObject->gameManager->camera == "D")
			return true;
		break;
	case MusicEnemyComponent::E:
		if (gameObject->gameManager->camera == "E")
			return true;
		break;
	case MusicEnemyComponent::F:
		if (gameObject->gameManager->camera == "F")
			return true;
		break;
	case MusicEnemyComponent::G:
		if (gameObject->gameManager->camera == "G")
			return true;
		break;
	case MusicEnemyComponent::H:
		if (gameObject->gameManager->camera == "H")
			return true;
		break;
	case MusicEnemyComponent::I:
		if (gameObject->gameManager->camera == "I")
			return true;
		break;
	case MusicEnemyComponent::J:
		if (gameObject->gameManager->camera == "J")
			return true;
		break;
	case MusicEnemyComponent::B:
		if (gameObject->gameManager->camera == "B")
			return true;
		break;
	default:
		return false;
		break;
	}

	return false;
}

void MusicEnemyComponent::move()
{
	switch (currentLocation)
	{
	case MusicEnemyComponent::C:
		gameObject->position = glm::vec3(7.6f, 0.0f, -19.824f);
		gameObject->rotation = glm::vec3(0.619f, 1.131f, -0.352f);
		break;
	case MusicEnemyComponent::D:
		gameObject->position = glm::vec3(15.530f, 0.0f, -32.160f);
		gameObject->rotation = glm::vec3(-0.352f, 2.957f, 0.264f);
		break;
	case MusicEnemyComponent::E:
		gameObject->position = glm::vec3(37.445f, 0.0f, -36.564f);
		gameObject->rotation = glm::vec3(-0.837, -4.267f, 1.058f);
		break;
	case MusicEnemyComponent::F:
		gameObject->position = glm::vec3(39.207f, 0.0f, -11.805f);
		gameObject->rotation = glm::vec3(0.705f, -1.288f, 1.058f);
		break;
	case MusicEnemyComponent::G:
		gameObject->position = glm::vec3(43.612f, 0.0f, -11.805f);
		gameObject->rotation = glm::vec3(-0.485f, 2.452f, 0.529f);
		break;
	case MusicEnemyComponent::H:
		gameObject->position = glm::vec3(34.032f, 0.0f, 23.348f);
		gameObject->rotation = glm::vec3(0.352f, 0.402f, 0.000f);
		break;
	case MusicEnemyComponent::I:
		gameObject->position = glm::vec3(18.173f, 0.0f, 22.466f);
		gameObject->rotation = glm::vec3(0.485, 0.579,  -0.088);
		break;
	case MusicEnemyComponent::J:
		gameObject->position = glm::vec3(-8.259f, 0.0f, 22.466f);
		gameObject->rotation = glm::vec3(0.441f, -0.700f, 0.529f);
		break;
	case MusicEnemyComponent::B:
		gameObject->position = glm::vec3(2.313f, 0.0f, -5.727f);
		gameObject->rotation = glm::vec3(-0.392f, -3.644f, 0.353f);
		break;
	default:
		break;
	}
}

void MusicEnemyComponent::stopPlaying()
{
	gameObject->position = glm::vec3(0.0f, 200.0f, 0.0f);
	if (musicPlay)
	{
		musicPlay->stop();
		musicPlay->drop();
	}

	isPlaying = false;
	timeBeforeNextAttack = (float)distribution(generator) + mininumTimeBeforeNextMove;
	currentLocation = getRandomLocation();
	attackTime = 44.0f;
	scareAwayTime = 4.0f;
}

void MusicEnemyComponent::jumpscare()
{
	gameObject->position = glm::vec3(-3.651f, -2.203f, -4.365f);
	gameObject->rotation = glm::vec3(-0.705f, -1.022f, 5.683f);

	gameObject->gameManager->player->rotation = glm::vec3(0.0f, 1.6f, 0.0f);
	gameObject->gameManager->player->getComponent<CameraComponent>()->cameraShakeTime = 3.0f;
	gameObject->gameManager->gameOver = true;
	gameObject->gameManager->playSound(GameManager::JUMPSCARE);
}

MusicEnemyComponent::MusicEnemyLocations MusicEnemyComponent::getRandomLocation()
{
	return (MusicEnemyLocations)positionDistribution(generator);
}

std::string MusicEnemyComponent::locationToString()
{
	switch (currentLocation)
	{
	case MusicEnemyComponent::C:
		return "C";
		break;
	case MusicEnemyComponent::D:
		return "D";
		break;
	case MusicEnemyComponent::E:
		return "E";
		break;
	case MusicEnemyComponent::F:
		return "F";
		break;
	case MusicEnemyComponent::G:
		return "G";
		break;
	case MusicEnemyComponent::H:
		return "H";
		break;
	case MusicEnemyComponent::I:
		return "I";
		break;
	case MusicEnemyComponent::J:
		return "J";
		break;
	case MusicEnemyComponent::B:
		return "B";
		break;
	default:
		return "Unknown";
		break;
	}

	return "Unknown";
}
