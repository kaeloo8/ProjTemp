#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"
#include "Pointer.h"

class SceneEloulou : public Scene
{
	std::vector<Entity*> entitylist;

	sf::RenderWindow* Win;
	Pointer* lPointer;

	Player* lPlayer;

	Monster* Skeleton;

	Entity* Fond;
	Entity* Button1;
	Entity* Button2;
	Entity* Button3;
	Entity* Button4;
	Entity* Button5;
	Entity* Button6;

public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
	void Load();
};

