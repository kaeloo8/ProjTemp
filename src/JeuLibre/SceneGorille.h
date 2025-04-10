#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pointer.h"
#include "CameraSys.h"
#include "UI.h"
#include "Bouton.h"
#include "Text.h"
#include "Drop.h"
#include "Debug.h"

class SceneGorille : public Scene
{
	std::vector<Entity*> entitylist;

	sf::RenderWindow* Win;
	Pointer* lPointer;

	CameraSys* cam;
	Player* lPlayer;

	UI* lUI;
	UI* Menu;
	UI* BackgroundScene;

	std::vector<UI*> lBoutton;
	std::vector<Drop*> lDrop;

	Text* lText;

	bool mOpen;


public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void SetName() override;
};
