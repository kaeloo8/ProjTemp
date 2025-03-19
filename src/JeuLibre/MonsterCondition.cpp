#include "pch.h"
#include "MonsterCondition.h"
#include "Monster.h"

#include <iostream>
#include <cmath> // Pour utiliser sqrt


bool DistanceToPlayerCondition::OnTest(Monster* pMonster) 
{
    if (pMonster->mTarget == nullptr) return false;

    float distance = sqrt(pow(pMonster->GetPosition().x - pMonster->mTarget->GetPosition().x, 2) +
        pow(pMonster->GetPosition().y - pMonster->mTarget->GetPosition().y, 2)); 
    if (distance < pMonster->SeeDistance)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool FarFromPlayerCondition::OnTest(Monster* pMonster) 
{
    if (pMonster->mTarget == nullptr) return false;

    float distance = sqrt(pow(pMonster->GetPosition().x - pMonster->mTarget->GetPosition().x, 2) +
        pow(pMonster->GetPosition().y - pMonster->mTarget->GetPosition().y, 2));
    return distance > pMonster->SeeDistance;
}