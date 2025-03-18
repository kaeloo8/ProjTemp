#pragma once
#include "entity.h"

class TileMap : public Entity
{
public :
	std::vector<std::vector<sf::Sprite>> lSprite;
	void OnUpdate() override;
	void create(std::string path);
};

