#include "pch.h"
#include "Monster.h"

Monster::Monster() : mState(MonsterState::Idle), isAttacking(false), isMoving(false)
{
    mIdleAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("skeleton_idle_strip6"),
        6,    // nombre de frames idle
        0.2f  // durée par frame idle
    );
    mWalkAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("skeleton_walk_strip8"),
        8,    // nombre de frames walk
        0.1f  // durée par frame walk
    );
    mAttackAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("skeleton_attack_strip7"),
        7,    // nombre de frames roll
        0.07f  // durée par frame roll
    );
}

Monster::~Monster()
{
    delete mWalkAnimator;
    delete mIdleAnimator;
    delete mAttackAnimator;
}

void Monster::OnAnimationUpdate()
{
    float dt = GetDeltaTime();

    // Mise à jour des animations selon l'état
    if (mState == MonsterState::Walking && mWalkAnimator) {
        mWalkAnimator->Update(dt);
    }
    else if (mState == MonsterState::Idle && mIdleAnimator) {
        mIdleAnimator->Update(dt);
    }
    else if (mState == MonsterState::Attacking && mAttackAnimator) {
        mAttackAnimator->Update(dt);
    }
}

void Monster::FaceRight()
{
    GetSprite()->setScale(std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
}

void Monster::FaceLeft()
{
    GetSprite()->setScale(-std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
}

void Monster::OnUpdate()
{
    OnAnimationUpdate();

    if (isAttacking)
    {
        SetState(MonsterState::Attacking);
        return;
    }
    else if (isMoving) {
        SetState(MonsterState::Walking);
    }
    else {
        SetState(MonsterState::Idle);
    }
}

void Monster::OnCollision(Entity* pCollidedWith)
{
}

void Monster::SetState(MonsterState state)
{
    if (mState != state)
    {
        mState = state;

        // Modification de l'image et réinitialisation de l'animation en fonction de l'état
        if (mState == MonsterState::Idle) {
            SetImage("skeleton_idle_strip6");
            if (mIdleAnimator) mIdleAnimator->Reset();
        }
        else if (mState == MonsterState::Walking) {
            SetImage("skeleton_walk_strip8");
            if (mWalkAnimator) mWalkAnimator->Reset();
        }
        else if (mState == MonsterState::Attacking) {
            SetImage("skeleton_attack_strip7");
            if (mAttackAnimator) mAttackAnimator->Reset();
        }

    }
}

void Monster::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}
