#include "EnemyComponent.h"
//#include "GameObject.h"
#include "GameManager.h"
#include <random>


float passedEnemyTime = glfwGetTime();
float mininumTimeBeforeNextMove = 15.0f;
int randomTimeBeforeNextMove = 16;
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution;

EnemyComponent::EnemyComponent(const std::vector<EnemyLocations>& enemyPath, const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& rotations)
{
	currentPathIndex = 0;
	this->enemyPath = enemyPath;
	this->positions = positions;
	this->rotations = rotations;
	currentLocation = this->enemyPath[currentPathIndex];
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::init()
{
	gameObject->position = positions.at(currentPathIndex);
	gameObject->rotation = rotations[currentPathIndex];
	std::random_device randomDevice;
	generator = std::default_random_engine(randomDevice());
	distribution = std::uniform_int_distribution<int>(1, randomTimeBeforeNextMove);
	moveTime = (float)distribution(generator) + mininumTimeBeforeNextMove;
}

void EnemyComponent::update(float elapsedTime)
{
	float currentTime = glfwGetTime();
	deltaTime = currentTime - passedEnemyTime;

	if (deltaTime > moveTime)
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
	currentLocation = enemyPath[currentPathIndex];
	gameObject->position = positions[currentPathIndex];
	gameObject->rotation = rotations[currentPathIndex];

}

bool EnemyComponent::tryToAttack()
{
	if (gameObject->gameManager->leftDoorClosed())
	{
		return false;
	}
	else return true;
}

void EnemyComponent::jumpscare()
{
	gameObject->position = jumpscarePosition;
	gameObject->rotation = jumpscareRotation;
	currentPathIndex = 0;
	gameObject->gameManager->playSound(GameManager::JUMPSCARE);
}
