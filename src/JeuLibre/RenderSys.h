#pragma once
#include <vector>

class Window;
class Entity;

class RenderSys
{
	Window* Windows;
	std::vector<Entity*> EntityList;
public :

	RenderSys();

	void CreateEntity();
	void Update();
};

