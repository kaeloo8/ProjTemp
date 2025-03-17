#pragma once

#include "Entity.h"
#include "Animator.h"
#include "PlayerPart.h"

enum class PlayerState {
    Idle,
    Walking,
    Sprinting,
    Dashing 
};


class Player : public Entity
{
private:
    PlayerPart* PlayerHair;
    PlayerPart* Hand;

    Animator* mWalkAnimator; 
    Animator* mIdleAnimator; 
    Animator* mSprintAnimator;
    Animator* mDashAnimator;
    PlayerState mState;

    void OnAnimationUpdate();

public:
    bool isMoving;
    bool isSprinting;
	bool isDashing;



	const char* PlayerHaircut = "shorthair_idle_strip9";

    Player(); 
    ~Player(); 

	float lastVelocityX, lastVelocityY;
	float dashVelocityX, dashVelocityY;
	float dashTimer;
    float dashCooldown = 0.f;  
    const float maxDashCooldown = 0.5f;  

    void FaceRight();
	void FaceLeft();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerState state);

    void SetImage(const char* path) override;
};
