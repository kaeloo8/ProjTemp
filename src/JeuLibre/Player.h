#pragma once

#include "Entity.h"
#include "Animator.h"

enum class PlayerState { Idle, Walking, Sprinting };

class Player : public Entity
{
private:
    Animator* mWalkAnimator; 
    Animator* mIdleAnimator; 
    Animator* mSprintAnimator;
    PlayerState mState;

public:
    bool isMoving;
    bool isSprinting;
    Player(); 
    ~Player(); 

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerState state);

    void SetImage(const char* path) override;
};
