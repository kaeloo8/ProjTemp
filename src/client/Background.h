#pragma once
#include "Entity.h"


class Background : public Entity
{
public:

	void Init(std::string m);
	virtual void Update(float deltaTime);
};

