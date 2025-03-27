#pragma once
#include "Entity.h"

class Hole : public Entity
{
public:

	Hole();
	~Hole();

	const char* PlantType;

	sf::Sprite Plant;

	std::string cSeed;
	std::string cLittlePlant;
	std::string cMiddlePlant;
	std::string cTallPlant;
	std::string cFinalPlant;

	float ActualPousse = 0;
	float TotalPousse = 100;
};

