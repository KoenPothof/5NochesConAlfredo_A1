#include "RunningEnemyComponent.h"
#include "GameObject.h"
#include "GameManager.h"
#include "CameraComponent.h"

//float passedEnemyTime;


RunningEnemyComponent::RunningEnemyComponent()
{
	passedEnemyTime = glfwGetTime();
	std::random_device randomDevice;
	generator = std::default_random_engine(randomDevice());
	distribution = std::uniform_int_distribution<int>(1, randomTimeBeforeNextMove);
	moveTime = (float)distribution(generator) + mininumTimeBeforeNextMove;
}

RunningEnemyComponent::~RunningEnemyComponent()
{
}

void RunningEnemyComponent::update(float elapsedTime)
{
	if (isFrozen)
	{
		return;
	}

	float currentTime = glfwGetTime();
	deltaTimeEnemy = currentTime - passedEnemyTime;

	if (deltaTimeEnemy > moveTime)
	{
		runningDone = false;
		gameObject->gameManager->playSound(GameManager::RUNNING);
		moveTime = (float)distribution(generator) + mininumTimeBeforeNextMove;
		passedEnemyTime = currentTime;
	}
	if (!runningDone)
	{
		startRunning(elapsedTime);
	}
}

void RunningEnemyComponent::init()
{
	gameObject->position = glm::vec3(12.184f, 20.0f, 1.850f);;
	gameObject->rotation = glm::vec3(0.0f, -1.551f, 0.0f);
}

void RunningEnemyComponent::startRunning(float elapsedTime)
{
	float targetX = -1.0f;
	gameObject->position.y = 0.0;
	if (gameObject->position.x >= targetX)
	{
		gameObject->position.x -= runningSpeed * elapsedTime;
	}
	else
	{
		if (tryToAttack())
		{
			jumpscare();
		}
		else
		{
			moveBack();
			runningDone = true;
		}
	}
}

void RunningEnemyComponent::moveBack()
{
	gameObject->position = glm::vec3(12.184f, 20.0f, 1.850f);
}

bool RunningEnemyComponent::tryToAttack()
{
	return !gameObject->gameManager->rightDoorClosed();
}

void RunningEnemyComponent::jumpscare()
{
	gameObject->position = glm::vec3(-3.651f, -2.203f, -4.365f);
	gameObject->rotation = glm::vec3(-0.705f, -1.022f, 5.683f);
	//gameObject->gameManager->gameOver = true;

	gameObject->gameManager->player->rotation = glm::vec3(0.0f, 1.6f, 0.0f);
	gameObject->gameManager->player->getComponent<CameraComponent>()->cameraShakeTime = 3.0f;
	gameObject->gameManager->gameOver = true;
	gameObject->gameManager->playSound(GameManager::JUMPSCARE);
}
