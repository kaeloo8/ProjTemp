#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "TileMap.h"

class SceneChevalier : public Scene
{

	sf::RenderWindow* Win;

	Entity* map;

	Player* lPlayer;

	Pointer* lPointer;



public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};
