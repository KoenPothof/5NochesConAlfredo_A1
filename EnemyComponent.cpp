#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(const std::vector<EnemyLocations> enemyPath, const std::vector<glm::vec3> positions, const std::vector<glm::vec3> rotations)
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
	if (currentPathIndex >= enemyPath.size())
	{
		if (enemyPath[enemyPath.size() - 1] == EnemyLocations::A)
		{
			if (tryToAttack())			
				jumpscare();			
			else
				moveBack();
		}
	}	
	else
	{
		currentLocation = enemyPath[currentPathIndex];
		gameObject->position = positions[currentPathIndex];
		gameObject->rotation = rotations[currentPathIndex];
	}

}

void EnemyComponent::moveBack()
{
	currentPathIndex = 0;
	currentLocation = enemyPath[currentPathIndex];
	gameObject->position = positions[currentPathIndex];
}

bool EnemyComponent::tryToAttack()
{
	return false;
}

void EnemyComponent::jumpscare()
{
}
