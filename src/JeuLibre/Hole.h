#pragma once
#include <SFML/System/Clock.hpp>
#include "Entity.h"
#include "Animator.h"
#include "Player.h"
#include "Plant.h"

enum class HoleState {
	Empty,
	Fill,
	Arosed,
	GrownOver
};

class Hole : public Entity
{
public:
    Hole();
    ~Hole();

	Entity* mVegetable;

	HoleState aState = HoleState::Empty;
	sf::Vector2i Adresse;

    void Planting(std::string _plant);
    Animator* mSpawnAnimation;

	void SetPlayer(Player* player) { mPlayer = player; }
	Player* mPlayer;

    std::string PlantType;

    Plant* Vegetable;

    void SetState(HoleState newState);

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;
};
