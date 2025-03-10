#pragma once
#include "vector.h"
#include "SFML/Graphics.hpp"

class Camera
{
	 sf::Vector2f CameraPos;
public :

	sf::Vector2f GetPos();
	float GetPosX();
	float GetPosY();

	void SetPos(sf::Vector2f Pos);
	void SetPos(float x, float y);
	void SetPosX(float PosX);
	void SetPosY(float PosY);

	void Add(float x, float y);

};

