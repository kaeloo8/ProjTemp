#pragma once
#include "Entity.h"
#include "Animator.h"
#include "PlayerPart.h"
#include "DamageZone.h"
#include "Debug.h"

enum class PlayerState {
    sIdle,
    sWalking,
    sSprinting,
    sAttacking,
    sDashing,
    sHurt,
    //peche
    sCasting,
    sWattering,
    sReeling,
    sCaught,
    //travail
    sGoToWork,
    sDig,
    sAxe,
    sMining,

    sCount
};

enum class PlayerMode {
    Attack,
    Dig,
    Pickaxe,
    Axe
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
    Animator* mMiningAnimator;
    //ez

    DamageZone* AttackArea = nullptr;

    void OnAnimationUpdate();

public:
    std::string GetCurrentStateName();
    bool isMoving;
    bool isSprinting;
	bool isDashing;
	bool isAttacking;
    bool isStunt;

    //bool d'action
    bool HasDug;

    PlayerState mState;
    PlayerMode mMode = PlayerMode::Attack;

    sf::Vector2f ActionPoint;

    bool Face_Left;

    int DamageDistance = 40;
    int PlayerDamage = 10;
    bool AtckActive;

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

    void SetActionPoint(float _x, float _y);

    void FaceRight();
	void FaceLeft();

    void ChangeHaircut(const char* haircut);

    void ToogleMode();
    void ChangeMod();
    void ChangeActionMod();
    void StateActionMod();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerState state);

    void cAttack();

    void SetImage(const char* path) override;
};
