#pragma once
#include "Entity.h"

class Player : public Entity
{
public :
	Player();
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};

