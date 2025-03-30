#pragma once
#include "Entity.h"

class Pointer : public Entity
{
public:
	sf::RenderWindow* Win;
	sf::Vector2f worldPos;

	Pointer();
	void ChangeI(const char* path);

	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};

