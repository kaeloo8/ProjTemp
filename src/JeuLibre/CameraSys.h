#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "Entity.h"
class CameraSys : public Entity
{
	sf::View camera;
public :
	CameraSys();
	sf::View getView();
	void OnUpdate() override;
};

