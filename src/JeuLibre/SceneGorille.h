#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "UI.h"
#include "OptionMenu.h"

class SceneGorille : public Scene
{
	std::vector<Entity*> entitylist;

	sf::RenderWindow* Win;
	OptionMenu* Options;
	Pointer* lPointer;

	Player* lPlayer;
	UI* LifeBar;
	UI* ButtonCancel;
	UI* ButtonValid;


public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};
