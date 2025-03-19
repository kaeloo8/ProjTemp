#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "UI.h"

class SceneGorille : public Scene
{
	std::vector<Entity*> entitylist;

	sf::RenderWindow* Win;
	Pointer* lPointer;

	Player* lPlayer;
	UI* Button;
	UI* Button2;


public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};
