#pragma once
#include "Entity.h"
#include "FillBar.h"
#include <SFML/Graphics.hpp>

class Player : public Entity
{
	bool CanShoot;
public:

	float MaxLife;
	float Life;
	float PlayerSpeed;
	float Angle;
	float Cooldown;
	float PosWorldX;
	float PosWorldY;
	std::string Name;
	Player();
	Player(sf::Vector2f PosPlayer);

	void OrientToMouse(sf::Vector2i mPos);
	void OrientTo(float rad);
	void SetSkin();
	void DamagePlayer(float damage);
	void HealPlayer(float heal);
	void SetLife(float l);
	float GetRad();
	float GetLife();
	void SetName(std::string N);
	std::string GetName();

	void OnUpdate() override;
	//void OnCollision(Entity* pCollidedWith) override;
	bool Shoot();

private:

};
