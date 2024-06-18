#pragma once
#include "Component.h"
#include <random>
class MusicEnemyComponent : public Component
{
public:

	enum MusicEnemyLocations
	{
		C = 0, D = 1, E = 2, F = 3, G = 4, H = 5, I = 6, J = 7, B = 8
	};

	MusicEnemyLocations currentLocation;
	bool isFrozen = true;
	bool isPlaying = false;

	float attackTime = 44.0f;
	float timeBeforeNextAttack = 25.0f;
	float scareAwayTime = 4.0f;

	MusicEnemyComponent();
	~MusicEnemyComponent();
	void update(float elapsedTime) override;
	void startPlaying();
	void move();
	void stopPlaying();
	void jumpscare();
	bool canScareAway();
	MusicEnemyLocations getRandomLocation();
	std::string locationToString();

private:
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	std::uniform_int_distribution<int> positionDistribution;

	const float mininumTimeBeforeNextMove = 0.0f;
	const int randomTimeBeforeNextMove = 15;

	float passedAttackTime = 0.0f;
	float lastAttackTime = attackTime;

	const int amountOfRooms = 9;
};

