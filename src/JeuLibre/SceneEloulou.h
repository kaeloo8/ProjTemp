#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"
#include "Pointer.h"
#include "Hole.h"
#include "Drop.h"
#include "Flore.h"
#include "CameraSys.h"
#include "BuildSystem.h"
#include "UI.h"

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

	std::vector<Hole*> lHole;
	std::vector<Drop*> lDrop;
	std::vector<Flore*> lFlore;
	std::vector<UI*> lPlayerModeUi;
	std::vector<UI*> listSeedUi;


	Monster* Skeleton;

	Entity* Mur1;

public:
	void addHole();
	void addVegetables();
	void cutTree();
	void mineStone();


	void HandleModeChange(sf::Keyboard::Key key, bool& keyPressed, PlayerMode mode, int uiIndex);
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
	void Load();
};

