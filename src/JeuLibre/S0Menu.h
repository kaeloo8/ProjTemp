#pragma once
#include "Scene.h"

class S0Menu : public Scene
{
public:

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void Load();
};

