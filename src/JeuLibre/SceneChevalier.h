#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "TileMap.h"
#include "CameraSys.h"
#include "Monster.h"
#include "SpawnSys.h"
#include "Entity.h"

class SceneChevalier : public Scene
{

	sf::RenderWindow* Win;

	TileMap* map;

	Player* lPlayer;

	Pointer* lPointer;

	CameraSys* cam;

	std::vector<Monster*> lEnnemie;

	std::vector<Entity*> lDoor;

	SpawnSys* SpawnArea;

	Entity* CamFocus;

	int Decalx;
	int Decaly;
	bool verifspawn;


public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};
