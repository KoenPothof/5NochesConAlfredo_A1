#include "EnemyComponent.h"
//#include "GameObject.h"
#include "GameManager.h"

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
}

void EnemyComponent::update(float elapsedTime)
{
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
}
