#pragma once
#include <vector>
#include "Component.h"
#include "tigl.h"
#include "GameObject.h"
class EnemyComponent : public Component
{
public:
	enum EnemyLocations
	{
		A, B, C, D, E, F, G, H, I, J, K, HALL_LEFT, HALL_RIGHT
	};

	EnemyComponent(const std::vector<EnemyLocations> enemyPath, const std::vector<glm::vec3> positions, const std::vector<glm::vec3> rotations);
	~EnemyComponent();

	void update(float elapsedTime) override;
	void init();
	void moveToNextRoom();
	void moveBack();
	bool tryToAttack();
	void jumpscare();
	inline EnemyLocations getCurrentLocation() { return currentLocation; }
private:
	std::vector<EnemyLocations> enemyPath;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> rotations;
	EnemyLocations currentLocation;
	unsigned int currentPathIndex = 0;
};

