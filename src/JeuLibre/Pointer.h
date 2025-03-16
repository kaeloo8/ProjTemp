#pragma once
#include "Entity.h"

class Pointer : public Entity
{
public:
	std::string Img = "Pointer";

	Pointer();
	void OnUpdate() override;
	//void OnCollision(Entity* pCollidedWith) override;
};

