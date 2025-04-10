#pragma once
#include "Entity.h"
#include "GameManager.h"
#include "Player.h"

class Drop : public Entity
{
	sf::Sprite mItemDrop;
	std::string cItemDrop;

	sf::Vector2f Velocity;

	float mLifeTime;
	float angle;

	bool mIsDropped;

public:
	Drop();
	
	bool mIsCollected = false;

	bool IsCollected();
	
	void SetVelocity(float speed);
	void IsDroped();
	void OnCollision(Entity* pOther) override;
	void SetImage(const char* path) override;
	void OnUpdate() override;
};

