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

	bool KeyGPressed;
	bool mIsDropped;

public:
	Drop();
	
	bool mIsCollected = false;

	bool IsCollected();

	void ItemDroped();
	void OnCollision(Entity* pOther) override;
	void OnUpdate() override;
};

