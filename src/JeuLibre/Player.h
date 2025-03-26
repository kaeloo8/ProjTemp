#pragma once
#include "Entity.h"
#include "Animator.h"
#include "PlayerPart.h"
#include "DamageZone.h"

enum class PlayerState {
    Idle,
    Walking,
    Sprinting,
	Attacking,
    Dashing 
};


class Player : public Entity
{
private:
    PlayerPart* PlayerHair;
    PlayerPart* PlayerHand;

    Animator* mWalkAnimator; 
    Animator* mIdleAnimator; 
    Animator* mSprintAnimator;
    Animator* mDashAnimator;
    Animator* mAttackAnimator;
    PlayerState mState;

    DamageZone* AttackArea = nullptr;

    void OnAnimationUpdate();

public:

    bool isMoving;
    bool isSprinting;
	bool isDashing;
	bool isAttacking;
    bool isStunt;

    bool isTurn;

    int DamageDistance = 40;

    float tBeforSwitch = 0;

	const char* PlayerHaircut = "shorthair_idle_strip9";

    Player(); 
    ~Player(); 

	float lastVelocityX, lastVelocityY;
	float dashVelocityX, dashVelocityY;

    float attackTimer;
	float attackCooldown = 0.f;
    const float attackDuration = 0.7f;

	float dashTimer;
    float dashCooldown = 0.f;  
    const float maxDashCooldown = 0.5f;  

    void FaceRight();
	void FaceLeft();

    void ChangeHaircut(const char* haircut);

    void ToogleMode();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerState state);

    void cAttack();

    void SetImage(const char* path) override;
};
