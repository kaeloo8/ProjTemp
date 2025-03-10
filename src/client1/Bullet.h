#pragma once
#include "Entity.h"
#include "FillBar.h"
#include <SFML/Graphics.hpp>
#include "Online.h"

class Online;

class Bullet : public Entity
{
	Online* OnLine;
public:
	float Damage;
	float Speed;
	float Angle;
	float tox;
	float toy;
	float posx;
	float posy;
	bool isDestroy;
	float LifeTime;

	Bullet();
	Bullet(sf::Vector2f PosPlayer);
	void Init(float x, float y, float tox, float toy, Online* reseau);

	void OnUpdate() override;

private:

};
