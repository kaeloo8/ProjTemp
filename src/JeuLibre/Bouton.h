#pragma once
#include "Entity.h"

class Bouton : public Entity
{
public : 
	sf::Texture ImgD, ImgH;

	Bouton();

	void OnCollision(Entity* pOther) override;
	void OnUpdate() override;
};

