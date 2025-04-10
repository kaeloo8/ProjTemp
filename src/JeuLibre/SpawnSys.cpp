#include "pch.h"
#include "SpawnSys.h"

SpawnSys::SpawnSys() {
	nSpawn = 0;
	CollideToActive = false;
	lPlayer = nullptr;
	EntityIn = false;
}

void SpawnSys::SetTarget(Player* p) {
	lPlayer = p;
}

void SpawnSys::SetCam(Entity* c) {
	camf = c;
}

void SpawnSys::KillAll() {
	for (auto e : lMonster) {
		e->DamageLife(9999999); // votre dieux vous suprimeras MOUAh AH AH 
	}
}

void SpawnSys::OnUpdate() {

	if (lMonster.size() > 0) {
		std::vector<Monster*> lt;
		for (auto e : lMonster) {
			if (!e->mToDestroy) {
				lt.push_back(e);
			}
		}
		lMonster.clear();
		lMonster = lt;
	}

	Boucle = false;
}

void SpawnSys::OnCollision(Entity* collidedWith) {
	if (Boucle == false) {
		Boucle = true;
		EntityIn = false;
	}
	if (collidedWith->mTag == GameManager::Tag::tEnnemie) {
		EntityIn = true;

	}
	
}

void SpawnSys::SetNumber(int n) {
	nSpawn = n;
}


void SpawnSys::Spawn() {

	std::cout << "spawn" << std::endl;
	for (int n = 0;n < nSpawn;n++) {
		int x = GetScale().x - GetPosition().x;
		int Sx = ((std::rand() % 401) - 200) + GetPosition().x;
		int y = GetScale().y - GetPosition().y;
		int Sy = ((std::rand() % 301) - 150) + GetPosition().y;
		int Dx = lPlayer->GetPosition().x - Sx;
		int Dy = lPlayer->GetPosition().y - Sy;
		if (Dx < 0)
			Dx *= -1;
		if (Dy < 0)
			Dy *= -1;

		if (Sx + Sy < 100)
			continue;

		sf::Vector2f pos; //((std::rand() % 401) - 200) + GetPosition().x, ((std::rand() % 301) - 150) + GetPosition().y);
		Monster* M;
		M = CreateEntity<Monster>("skeleton_idle_strip6");
		M->AddCircleHitbox();
		M->MonsterOption(true, true, true, true);
		M->InitMonster("skeleton");
		M->SetScale(3, 3);
		M->SetOrigin(0.5f, 0.5f);
		M->SetPosition(Sx,Sy);
		M->SetInitialPosition();
		M->SetSpeed(100);
		M->SetTarget(lPlayer);
		M->Layout = 2;
		lMonster.push_back(M);
	}
}


void SpawnSys::move(sf::Vector2f pos) {
	SetPosition(pos.x,pos.y);
	for (auto coord : lCoordAlreadySpawn) {
		if (pos.x == coord.x && pos.y == coord.y) {
			return;
		}
	}
	Spawn();
	lCoordAlreadySpawn.push_back({ pos.x, pos.y });
}