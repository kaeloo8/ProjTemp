#pragma once
#include "SFML/Graphics.hpp"

class TimeSystem
{
	sf::Clock clock;
	float DeltaTime;
public :
	float GetDeltaTime();
	void UpdateDeltaTime();
};

