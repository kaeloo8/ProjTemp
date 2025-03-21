#include "pch.h"
#include "MonsterAction.h"
#include "Monster.h"
#include "Debug.h"
#include <iostream>


void sIdle_Action::Start(Monster* pMonster)
{
    pMonster->isMoving = false;
    std::cout << "IDle" << std::endl;
    pMonster->SetImage("skeleton_idle_strip6");
    if (pMonster->mIdleAnimator) pMonster->mIdleAnimator->Reset();
    pMonster->LineColor = sf::Color::Blue;
}

void sIdle_Action::Update(Monster* pMonster) 
{
    if (pMonster->mTarget != nullptr)
    {
    }
}

void sIdle_Action::End(Monster* pMonster)
{
}

void sFollowPlayer_Action::Start(Monster* pMonster) 
{
    pMonster->isMoving = true;
    std::cout << "Follow" << std::endl;
    pMonster->SetImage("skeleton_walk_strip8");
    if (pMonster->mWalkAnimator) pMonster->mWalkAnimator->Reset();
    pMonster->LineColor = sf::Color::Green;
}

void sFollowPlayer_Action::Update(Monster* pMonster) 
{
    if (pMonster->mTarget != nullptr)
    {
        pMonster->GoToPosition(pMonster->mTarget->GetPosition().x, pMonster->mTarget->GetPosition().y, pMonster->mSpeed );
    }
}

void sFollowPlayer_Action::End(Monster* pMonster) 
{
    pMonster->isMoving = false;
    pMonster->StopGo();
}


void sAttack_Action::Start(Monster* pMonster) 
{
    pMonster->isAttacking = true;
    pMonster->isMoving = false;
    std::cout << "Attack" << std::endl;
    pMonster->SetImage("skeleton_attack_strip7");
    if (pMonster->mAttackAnimator) pMonster->mAttackAnimator->Reset();
    pMonster->LineColor = sf::Color::Magenta;
}

void sAttack_Action::Update(Monster* pMonster) 
{

}

void sAttack_Action::End(Monster* pMonster) 
{
    pMonster->isAttacking = false;
}

void sReturnToPosition_Action::Start(Monster* pMonster) 
{
    pMonster->isMoving = true;
    std::cout << "goBack" << std::endl;
    pMonster->SetImage("skeleton_walk_strip8");
    if (pMonster->mWalkAnimator) pMonster->mWalkAnimator->Reset();
    pMonster->LineColor = sf::Color::Red;
}

void sReturnToPosition_Action::Update(Monster* pMonster) 
{
    pMonster->GoToPosition(pMonster->InitialPosition.x, pMonster->InitialPosition.y, pMonster->mSpeed);
}

void sReturnToPosition_Action::End(Monster* pMonster) 
{
    pMonster->StopGo();
    pMonster->isMoving = false;
}

