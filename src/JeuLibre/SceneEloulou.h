#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"

class SceneEloulou : public Scene
{
	std::vector<Entity*> entitylist;

	sf::RenderWindow* Win;
	Pointer* lPointer;

	Player* lPlayer;
	Entity* Fond;

public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
	void Load();
};

