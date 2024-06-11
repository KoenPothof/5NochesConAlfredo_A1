#pragma once
#include "Component.h"
#include <random>
class RunningEnemyComponent : public Component
{
public:
	bool isFrozen = true;
	float deltaTimeEnemy = 0.0f;
	float moveTime = 0.0f;
	RunningEnemyComponent();
	~RunningEnemyComponent();
	void update(float elapsedTime) override;
	void init();
	void startRunning(float elapsedTime);
	void moveBack();
	bool tryToAttack();
	void jumpscare();

private:
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

	float mininumTimeBeforeNextMove = 30.0f;
	int randomTimeBeforeNextMove = 20;
	bool runningDone = true;
	float runningSpeed = 2.15f;
	float passedEnemyTime = 0.0f;

};

