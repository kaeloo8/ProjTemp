#include "pch.h"
#include "MonsterCondition.h"
#include "Monster.h"

#include <iostream>
#include <cmath> // Pour utiliser sqrt

bool AttackDistance::OnTest(Monster* pMonster)
{
    if (!pMonster || !pMonster->mTarget) return false;
    if (pMonster->isAttacking == true) return true;

    float distanceSquared = pMonster->GetDistanceTo(pMonster->mTarget);
    float AttackDistanceSquared = pMonster->AttackDistance * pMonster->AttackDistance;

    return distanceSquared < AttackDistanceSquared;
}

bool CanSeeThePlayer::OnTest(Monster* pMonster)
{
    if (!pMonster || !pMonster->mTarget) return false;
    
    float distanceSquared = pMonster->GetDistanceTo(pMonster->mTarget);
    float seeDistanceSquared = pMonster->SeeDistance * pMonster->SeeDistance;

    return distanceSquared < seeDistanceSquared;
}

bool IsAtInitialPosition::OnTest(Monster* pMonster)
{
    if (!pMonster || !pMonster->mTarget) return false;

    if (pMonster->GetPosition() == pMonster->InitialPosition)
    {
        return 1;
    }
    else {
        return 0;
    }
}
