#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"
#include "Pointer.h"
#include "CameraSys.h"
#include "BuildSystem.h"

class SceneEloulou : public Scene
{

	std::vector<Entity*> entitylist;

	TileMap* Ocean;
	TileMap* map;

	CameraSys* Cam;

	sf::RenderWindow* Win;
	Pointer* lPointer;

	Player* lPlayer;
	BuildSystem* lBuild;

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

