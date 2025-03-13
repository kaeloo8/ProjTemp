#include "pch.h"
#include "SceneManager.h"
#include <iostream>

void SceneManager::setScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
}

void SceneManager::handleEvent(sf::Event& event) {
    if (currentScene) currentScene->handleEvent(event);
}

void SceneManager::update(float dt) {
    if (currentScene) currentScene->update(dt);
}

void SceneManager::render(sf::RenderWindow& window) {
    if (currentScene) currentScene->render(window);
}