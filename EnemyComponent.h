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
		A, B, C, D, E, F, G, H
	};

	EnemyComponent(const std::vector<EnemyLocations>& enemyPath, const std::vector<glm::vec3>& positions);
	~EnemyComponent();

	void update(float elapsedTime) override;
	void moveToNextRoom();
	void moveBack();
	void tryToAttack();
	void jumpscare();
private:
	std::vector<EnemyLocations> enemyPath;
	std::vector<glm::vec3> positions;
	EnemyLocations currentLocation;
	int currentPathIndex = 0;
};

