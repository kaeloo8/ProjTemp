#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "UI.h"

class S0Menu : public Scene
{
	std::vector<Entity*> entitylist;

	sf::RenderWindow* Win;
	Pointer* lPointer;
	
	UI* lUI;

	Entity* Fond;
public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};

