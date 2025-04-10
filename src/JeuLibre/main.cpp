#include "pch.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "SceneEloulou.h"

int main() {
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "GameScene");

	pInstance->LaunchScene<SceneEloulou>();

	return 0;
}
