#pragma once

#include "Condition.h"
#include "Monster.h"

class DistanceToPlayerCondition : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class FarFromPlayerCondition : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};
