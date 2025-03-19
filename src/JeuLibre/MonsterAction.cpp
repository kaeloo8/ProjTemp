#include "pch.h"
#include "MonsterAction.h"
#include "Monster.h"
#include "Debug.h"
#include <iostream>


void sIdle_Action::Start(Monster* pMonster)
{
    pMonster->isMoving = true;
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
}

void sFollowPlayer_Action::Update(Monster* pMonster) 
{
    if (pMonster->mTarget != nullptr)
    {
        // Déplacer le monstre vers le joueur
        float dt = GameManager::Get()->GetDeltaTime();

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
}

void sReturnToPosition_Action::Update(Monster* pMonster) 
{
    // Déplacer le monstre vers sa position initiale
    float dt = GameManager::Get()->GetDeltaTime();
    pMonster->GoToPosition(pMonster->mTarget->GetPosition().x, pMonster->mTarget->GetPosition().y, pMonster->mSpeed * dt);
}

void sReturnToPosition_Action::End(Monster* pMonster) 
{
    pMonster->isMoving = false;
}

