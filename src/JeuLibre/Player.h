#pragma once

#include "Entity.h"
#include "Animator.h"
#include "Hair.h"

enum class PlayerState {
    Idle,
    Walking,
    Sprinting,
    Dashing 
};


class Player : public Entity
{
private:
	Hair* PlayerHair;
    Animator* mWalkAnimator; 
    Animator* mIdleAnimator; 
    Animator* mSprintAnimator;
    Animator* mDashAnimator;
    PlayerState mState;

    std::atomic<bool> isAnimationThreadRunning;  // Variable atomique pour gérer le thread d'animation
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
