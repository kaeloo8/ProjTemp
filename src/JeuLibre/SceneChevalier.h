#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "TileMap.h"
#include "CameraSys.h"
#include "Monster.h"

class SceneChevalier : public Scene
{

	sf::RenderWindow* Win;

	TileMap* map;

	Player* lPlayer;

	Pointer* lPointer;

	CameraSys* cam;

	std::vector<Monster*> lEnnemie;


public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};
