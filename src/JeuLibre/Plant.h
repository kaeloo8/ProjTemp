#pragma once
#include "Entity.h"


class Plant : public Entity
{
public:
	Plant();
	~Plant();

    std::string PlantType;
    std::string cSeed;
    std::string cLittlePlant;
    std::string cTallPlant;
    std::string cFinalPlant;

    float ActualPousse = 0;
    float TotalPousse = 100;

    sf::Clock pousseClock;

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;
};

