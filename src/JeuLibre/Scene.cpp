#include "pch.h"
#include "Scene.h"
#include "GameManager.h"

int Scene::GetWindowWidth() const
{
	return mpGameManager->widthWin;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->heightWin;
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->DeltaTime;
}