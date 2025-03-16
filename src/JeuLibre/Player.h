#pragma once

#include "Entity.h"
#include "Animator.h"

enum class PlayerState { Idle, Walking };

class Player : public Entity
{
private:
    Animator* mWalkAnimator; 
    Animator* mIdleAnimator; 
    PlayerState mState;

public:
    Player(); 
    ~Player(); 

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerState state);

    void SetImage(const char* path) override;
};
