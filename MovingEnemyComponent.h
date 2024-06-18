#pragma once
#include "Component.h"
#include <random>
class MovingEnemyComponent : public Component
{
public:

	enum MovingEnemyState
	{
		STAGE_1,
		STAGE_2,
		STAGE_LEFT1,
		STAGE_LEFT2,
		STAGE_RIGHT1,
		STAGE_RIGHT2,
	};

	bool enemyIsMoving = false;
	bool isFrozen = true;

	MovingEnemyComponent();
	~MovingEnemyComponent();
	void update(float elapsedTime);
	void startMoving(float elapsedTime);
	void moveBack();
	bool tryToAttack();
	void jumpscare();

private:
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

	MovingEnemyState state = STAGE_1;
	float moveSpeed = 0.5f;
	int amountOfAttacks = 0;
};

