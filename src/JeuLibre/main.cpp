#include "pch.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "S0Menu.h"

int main() {
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "GameScene");

	pInstance->LaunchScene<S0Menu>();

	return 0;
}
