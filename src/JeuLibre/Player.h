#pragma once
#include "Entity.h"
#include "Animator.h"
#include "PlayerPart.h"
#include "DamageZone.h"

enum class PlayerState {
    sIdle,
    sWalking,
    sSprinting,
    sAttacking,
    sDashing,
    sHurt,
    sCasting,
    sReeling,
    sCaught,
    sDig,
    sAxe,
    sMinning,

    sCount
};


class Player : public Entity
{
private:
    PlayerPart* PlayerHair;
    PlayerPart* PlayerHand;

    Animator* mIdleAnimator;
    Animator* mWalkAnimator;
    Animator* mSprintAnimator;
    Animator* mAttackAnimator;
    Animator* mDashAnimator;
    Animator* mHurtAnimator;
    //PECHE
    Animator* mCastingAnimator;
    Animator* mWatteringAnimator;
    Animator* mReelingAnimator;
    Animator* mCaughtAnimator;
    //MINE
    Animator* mDigAnimator;
    Animator* mAxeAnimator;
    Animator* mMinningAnimator;
    //ez
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
