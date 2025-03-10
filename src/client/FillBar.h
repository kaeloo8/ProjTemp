#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class FillBar : public Entity
{
public:
	sf::RectangleShape Background;
	sf::RectangleShape Bar;

	float Heigh;
	float MaxSize;
	float Fill;

	FillBar();

	void SetFill(float x);
	float GetFill();

	void OnUpdate() override;

private:


};