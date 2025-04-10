#pragma once
#include "Monster.h"
#include "Entity.h"
#include "Player.h"

class SpawnSys : public Entity
{
public:
	std::vector< Monster*> lMonster;
	std::vector<sf::Vector2f> lCoordAlreadySpawn;
	Player* lPlayer;
	Entity* camf;
	int nSpawn;
	bool CollideToActive;
	bool EntityIn;
	bool Boucle;
	
	SpawnSys();
	void SetTarget(Player* p);
	void SetCam(Entity* c);
	void SetNumber(int n);
	void KillAll();
	bool HaveEntityIn();
	void move(sf::Vector2f pos);
	void Spawn();
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
};

