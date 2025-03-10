#include "pch.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#include "GameManager.h"
#include "ShootThemUp.h"

#include <cstdlib>
#include <crtdbg.h>


int main() 
{
    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindowGM(1280, 720, "GameScene 2");

	pInstance->LaunchScene<ShootThemUp>();

	return 0;
}