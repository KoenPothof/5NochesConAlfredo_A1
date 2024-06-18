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
	}

	if (isPlaying)
	{
		if (attackTime >= lastAttackTime)
		{
			musicPlay = soundEngine->play2D("assets/sounds/muziekbeest.mp3", false, false, true);
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
		break;
	case MusicEnemyComponent::D:
		break;
	case MusicEnemyComponent::E:
		break;
	case MusicEnemyComponent::F:
		break;
	case MusicEnemyComponent::G:
		break;
	case MusicEnemyComponent::H:
		break;
	case MusicEnemyComponent::I:
		break;
	case MusicEnemyComponent::J:
		break;
	case MusicEnemyComponent::B:
		break;
	default:
		break;
	}
}

void MusicEnemyComponent::stopPlaying()
{
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
