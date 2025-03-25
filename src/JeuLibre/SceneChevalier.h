#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "TileMap.h"
#include "CameraSys.h"
#include "Monster.h"
#include "Entity.h"

class SceneChevalier : public Scene
{

	sf::RenderWindow* Win;

	TileMap* map;

	Player* lPlayer;

	Pointer* lPointer;

	CameraSys* cam;

	std::vector<Monster*> lEnnemie;

	std::vector<Entity*> lColide;

	Entity* CamFocus;

	int Decalx;
	int Decaly;


public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};
