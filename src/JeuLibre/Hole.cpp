#include "pch.h"
#include "Hole.h"

Hole::Hole()
{
    mSpawnAnimation = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_idle_strip9"), 9, 0.2f);
}

Hole::~Hole()
{
}
