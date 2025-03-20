#pragma once

#include "Action.h"
#include "Monster.h"

class sIdle_Action : public Action<Monster>
{
public:
	void Start(Monster* pMonster) override;
	void Update(Monster* pMonster) override;
	void End(Monster* pMonster) override;
};

class sFollowPlayer_Action : public Action<Monster>
{
public:
	void Start(Monster* pMonster) override;
	void Update(Monster* pMonster) override;
	void End(Monster* pMonster) override;
};


class sAttack_Action : public Action<Monster>
{
public:
	void Start(Monster* pMonster) override;
	void Update(Monster* pMonster) override;
	void End(Monster* pMonster) override;
};


class sReturnToPosition_Action : public Action<Monster>
{
public:
	void Start(Monster* pMonster) override;
	void Update(Monster* pMonster) override;
	void End(Monster* pMonster) override;
};