#pragma once
#include "Entity.h"
#include "GameManager.h"

class DamageZone : public Entity
{
public :
	bool UniqueColide = false;
	float LifeTime = 0;
	int Damage = 0;
	std::vector<GameManager::Tag> lTagIgnore;

	void OnUpdate() override;
	void IgnoreTag(GameManager::Tag t) { lTagIgnore.push_back(t); }
	void OnCollision(Entity* pCollidedWith) override;
};

