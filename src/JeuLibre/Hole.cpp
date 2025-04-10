#include "pch.h"
#include "Hole.h"
#include "Plant.h"
#include "Entity.h"

Hole::Hole()
    : Vegetable(nullptr), mPlayer(nullptr), mSpawnAnimation(nullptr)
{
	hasFixedLayout = true;
}


Hole::~Hole()
{
}

void Hole::Planting(std::string _plant)
{
	SetState(HoleState::Fill);
    mVegetable = CreateEntity<Plant>("carrot_01");
    mVegetable->SetOrigin(0.5, 0.5);
    mVegetable->SetPosition(GetPosition().x + mSprite.getGlobalBounds().width, GetPosition().y + mSprite.getGlobalBounds().height);
    mVegetable->SetSize(50, 50);
    mVegetable->Layout = 10;
}

void Hole::SetState(HoleState newState)
{
    if (aState != newState) {
        aState = newState;

        switch (aState) {
        case HoleState::Empty:
            break;
        case HoleState::Fill:
            break;
        case HoleState::Arosed:
            break;
        case HoleState::GrownOver:
            break;
        }
    }
}

void Hole::OnUpdate()
{

}

void Hole::OnCollision(Entity* pCollidedWith)
{
    
}

void Hole::SetImage(const char* path)
{
}
