#include "EnemyComponent.h"
//#include "GameObject.h"
#include "GameManager.h"
#include "CameraComponent.h"

float mininumTimeBeforeNextMove = 15.0f;
int randomTimeBeforeNextMove = 16;

EnemyComponent::EnemyComponent(const std::vector<EnemyLocations>& enemyPath, const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& rotations)
{
	currentPathIndex = 0;
	this->enemyPath = enemyPath;
	this->positions = positions;
	this->rotations = rotations;
	currentLocation = this->enemyPath[currentPathIndex];
	passedEnemyTime = glfwGetTime();

	std::random_device randomDevice;
	generator = std::default_random_engine(randomDevice());
	distribution = std::uniform_int_distribution<int>(1, randomTimeBeforeNextMove);
	moveTime = (float)distribution(generator) + mininumTimeBeforeNextMove;
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::init()
{
	gameObject->position = positions.at(currentPathIndex);
	gameObject->rotation = rotations[currentPathIndex];
}

void EnemyComponent::update(float elapsedTime)
{
	if (isFrozen)
	{
		//passedEnemyTime = glfwGetTime();
		return;
	}
	
	float currentTime = glfwGetTime();
	deltaTimeEnemy = currentTime - passedEnemyTime;

	if (deltaTimeEnemy > moveTime)
	{
		moveToNextRoom();
		moveTime = (float)distribution(generator) + mininumTimeBeforeNextMove;
		passedEnemyTime = currentTime;
	}
}

void EnemyComponent::moveToNextRoom()
{
	currentPathIndex++;
	gameObject->gameManager->playSound(GameManager::BEWEEGBEEST);
	currentLocation = enemyPath[currentPathIndex];
	if (currentLocation == A)
	{
		if (tryToAttack())
		{
			jumpscare();
		}
		else
		{
			moveBack();
		}
	}
	else
	{
		gameObject->position = positions[currentPathIndex];
		gameObject->rotation = rotations[currentPathIndex];
	}

}

void EnemyComponent::moveBack()
{
	currentPathIndex = 0;
	currentPathIndex = (int)distribution(generator) % 3;
	currentLocation = enemyPath[currentPathIndex];
	gameObject->position = positions[currentPathIndex];
	gameObject->rotation = rotations[currentPathIndex];

}

bool EnemyComponent::tryToAttack()
{
	if (attackFromLeft) return !gameObject->gameManager->leftDoorClosed();
	
	else return !gameObject->gameManager->rightDoorClosed();
}

void EnemyComponent::jumpscare()
{
	gameObject->position = jumpscarePosition;
	gameObject->rotation = jumpscareRotation;
	currentPathIndex = 0;

	gameObject->gameManager->player->rotation = glm::vec3(0.0f, 1.6f, 0.0f);
	gameObject->gameManager->player->getComponent<CameraComponent>()->cameraShakeTime = 3.0f;
	gameObject->gameManager->gameOver = true;
	gameObject->gameManager->playSound(GameManager::JUMPSCARE);
}
