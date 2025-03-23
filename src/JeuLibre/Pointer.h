#pragma once
#include "Entity.h"

class Pointer : public Entity
{
public:
	sf::RenderWindow* Win;

	Pointer();
	void OnUpdate() override;
	//void OnCollision(Entity* pCollidedWith) override;
};

