#include "pch.h"
#include "MonsterAction.h"
#include "Monster.h"
#include "Debug.h"
#include <iostream>


void sIdle_Action::Start(Monster* pMonster)
{
    pMonster->isMoving = false;
    pMonster->SetState(Monster::State::sIdle);
    std::cout << "IDle" << std::endl;
}

void sIdle_Action::Update(Monster* pMonster) 
{
    if (pMonster->mTarget != nullptr)
    {
    }
}

void sIdle_Action::End(Monster* pMonster)
{
    pMonster->isMoving = false;
}

void sFollowPlayer_Action::Start(Monster* pMonster) 
{
    pMonster->isMoving = true;
    pMonster->SetState(Monster::State::sWalk);
    std::cout << "Follow" << std::endl;
}

void sFollowPlayer_Action::Update(Monster* pMonster) 
{
    if (pMonster->mTarget != nullptr)
    {
        pMonster->GoToDirection(pMonster->mTarget->GetPosition().x, pMonster->mTarget->GetPosition().y, pMonster->mSpeed );
    }
}

void sFollowPlayer_Action::End(Monster* pMonster) 
{
    pMonster->isMoving = false;
}


void sAttack_Action::Start(Monster* pMonster) 
{
    pMonster->isAttacking = true;
    pMonster->SetState(Monster::State::sAttack);
    std::cout << "Attack" << std::endl;
}

void sAttack_Action::Update(Monster* pMonster) 
{
    // Logique d'attaque (lancer une attaque, vérification de collision, etc.)
}

void sAttack_Action::End(Monster* pMonster) 
{
    pMonster->isAttacking = false;
}

void sReturnToPosition_Action::Start(Monster* pMonster) 
{
    pMonster->isMoving = true;
    pMonster->SetState(Monster::State::sGoBack);
    std::cout << "goBack" << std::endl;
}

void sReturnToPosition_Action::Update(Monster* pMonster) 
{
    // Déplacer le monstre vers sa position initiale
    float dt = GameManager::Get()->GetDeltaTime();
    pMonster->GoToDirection(pMonster->InitialPosition.x, pMonster->InitialPosition.y, pMonster->mSpeed);
}

void sReturnToPosition_Action::End(Monster* pMonster) 
{
    pMonster->isMoving = false;
}

