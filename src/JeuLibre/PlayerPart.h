#pragma once

#include "Entity.h"
#include "Animator.h"

enum class PlayerPartState {
    sIdle,
    sWalking,
    sSprinting,
	sSwim,
    sAttacking,
    sDashing,
    sHurt,
    //peche
    sCasting,
    sWattering,
    sReeling,
    sCaught,
    //travail
    sDig,
    sAxe,
    sMining,

    sCount
};

class PlayerPart : public Entity
{
private:
    Animator* mIdleAnimator;
    Animator* mWalkAnimator;
    Animator* mSprintAnimator;
	Animator* mSwimAnimator;
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
    Animator* mMiningAnimator;

    PlayerPartState mState;

    std::string PartIdle;
    std::string PartWalk;
    std::string PartSprint;
	std::string PartSwim;
    std::string PartAttack;
    std::string PartDash;
    std::string PartHurt;
    //PECHE
    std::string PartCasting;
    std::string PartWattering;
    std::string PartReeling;
    std::string PartCaught;
    //MINE
    std::string PartDig;
    std::string PartAxe;
    std::string PartMining;

    Entity* mOwner = nullptr; 

public:
    const char* BodyPartName;

    bool isMoving;
    bool isSprinting;
    bool isDashing;

    PlayerPart();
    ~PlayerPart();

    float lastVelocityX, lastVelocityY;
    float dashVelocityX, dashVelocityY;
    float dashTimer;
    float dashCooldown = 0.f;
    const float maxDashCooldown = 0.5f;

    void InitBodyPart(const char* partName);
    void Clearanimation();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerPartState state);
    void SetOwner(Entity* owner);
    Entity* GetOwner() const;

    void SetImage(const char* path) override;
    void SetImage(std::string path);
};
