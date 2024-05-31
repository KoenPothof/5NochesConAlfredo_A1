#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(const std::vector<EnemyLocations>& enemyPath, const std::vector<glm::vec3>& positions)
{
	this->enemyPath = enemyPath;
	this->positions = positions;
	currentLocation = this->enemyPath[currentPathIndex];
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::update(float elapsedTime)
{
}

void EnemyComponent::moveToNextRoom()
{
	currentPathIndex++;
	if (currentPathIndex >= enemyPath.size())
	{
		tryToAttack();
	}	
	else
	{
		currentLocation = enemyPath[currentPathIndex];
		gameObject->position = positions[currentPathIndex];
	}

}

void EnemyComponent::moveBack()
{
}

void EnemyComponent::tryToAttack()
{
}

void EnemyComponent::jumpscare()
{
}
