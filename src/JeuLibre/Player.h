#pragma once

#include "Entity.h"
#include "Animator.h"

enum class PlayerState {
    Idle,
    Walking,
    Sprinting,
    Dashing 
};


class Player : public Entity
{
private:
    Animator* mWalkAnimator; 
    Animator* mIdleAnimator; 
    Animator* mSprintAnimator;
    Animator* mDashAnimator;
    PlayerState mState;

public:
    bool isMoving;
    bool isSprinting;
	bool isDashing;

    Player(); 
    ~Player(); 

	float lastVelocityX, lastVelocityY;
	float dashVelocityX, dashVelocityY;
	float dashTimer;
    float dashCooldown = 0.f;  
    const float maxDashCooldown = 0.5f;  


    void OnUpdate() override;
    void HandleInput(float dt);
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerState state);

    void SetImage(const char* path) override;
};
