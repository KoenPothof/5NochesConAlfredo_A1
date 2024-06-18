#include "MovingEnemyComponent.h"
#include "GameObject.h"
#include "GameManager.h"

MovingEnemyComponent::MovingEnemyComponent()
{
}

MovingEnemyComponent::~MovingEnemyComponent()
{
}

void MovingEnemyComponent::update(float elapsedTime)
{
	if (isFrozen)
	{
		return;
	}

	if (enemyIsMoving)
	{
		startMoving(elapsedTime);
	}
	else
	{
		
	}
}

void MovingEnemyComponent::startMoving(float elapsedTime)
{

}

void MovingEnemyComponent::moveBack()
{
	enemyIsMoving = false;
}

bool MovingEnemyComponent::tryToAttack()
{
	if (state == STAGE_LEFT2)
		return gameObject->gameManager->leftDoorClosed();
	
	else return gameObject->gameManager->rightDoorClosed();
}

void MovingEnemyComponent::jumpscare()
{
}
