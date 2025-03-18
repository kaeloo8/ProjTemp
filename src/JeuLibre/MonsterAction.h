#pragma once

#include "Action.h"
#include "Monster.h"

class sIdle_Action : public Action<Monster>
{
public:
	void Start(Monster* pPlant) override;
	void Update(Monster* pPlant) override;
	void End(Monster* pPlant) override;
};


class sStepBack_Action : public Action<Monster>
{
public:
	void Start(Monster* pPlant) override;
	void Update(Monster* pPlant) override;
	void End(Monster* pPlant) override;
};


class sAdvance_Action : public Action<Monster>
{
public:
	void Start(Monster* pPlant) override;
	void Update(Monster* pPlant) override;
	void End(Monster* pPlant) override;
};


class sRun_Action : public Action<Monster>
{
public:
	void Start(Monster* pPlant) override;
	void Update(Monster* pPlant) override;
	void End(Monster* pPlant) override;
};
