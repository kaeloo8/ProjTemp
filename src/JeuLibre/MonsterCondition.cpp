#include "pch.h"
#include "MonsterCondition.h"
#include "Monster.h"

#include <iostream>
#include <cmath> // Pour utiliser sqrt

bool AttackThePlayerCondition::OnTest(Monster* pMonster)
{
    if (!pMonster || !pMonster->mTarget) return false;

    float dx = pMonster->GetPosition().x - pMonster->mTarget->GetPosition().x;
    float dy = pMonster->GetPosition().y - pMonster->mTarget->GetPosition().y;
    float distanceSquared = dx * dx + dy * dy;
    float AttackDistanceSquared = pMonster->AttackDistance * pMonster->AttackDistance;

    return distanceSquared < AttackDistanceSquared;
}

bool DistanceToPlayerCondition::OnTest(Monster* pMonster)
{
    if (!pMonster || !pMonster->mTarget) return false;

    float dx = pMonster->GetPosition().x - pMonster->mTarget->GetPosition().x;
    float dy = pMonster->GetPosition().y - pMonster->mTarget->GetPosition().y;
    float distanceSquared = dx * dx + dy * dy;
    float seeDistanceSquared = pMonster->SeeDistance * pMonster->SeeDistance;

    return distanceSquared < seeDistanceSquared;
}

bool FarFromPlayerCondition::OnTest(Monster* pMonster)
{
    if (!pMonster || !pMonster->mTarget) return false;

    float dx = pMonster->GetPosition().x - pMonster->mTarget->GetPosition().x;
    float dy = pMonster->GetPosition().y - pMonster->mTarget->GetPosition().y;
    float distanceSquared = dx * dx + dy * dy;
    float seeDistanceSquared = pMonster->SeeDistance * pMonster->SeeDistance;

    return distanceSquared > seeDistanceSquared;
}
