#include "EnemyComponent.h"
//#include "GameObject.h"
#include "GameManager.h"
#include <random>
#include "CameraComponent.h"


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
	if (isFrozen)
	{
		passedEnemyTime = glfwGetTime();
		return;
	}
	
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
	gameObject->position = glm::vec3(-0.427f, -3.660f, -4.763f);
	gameObject->rotation = glm::vec3(0.0f, -2.519f, 0.0f);
	currentPathIndex = 0;

	gameObject->gameManager->player->rotation = glm::vec3(0.0f, 1.6f, 0.0f);
	gameObject->gameManager->player->getComponent<CameraComponent>()->cameraShakeTime = 3.0f;
	gameObject->gameManager->gameOver = true;
}
