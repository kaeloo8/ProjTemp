#include "pch.h"
#include <SFML/Graphics.hpp>
#include "assetmanager.h"
#include "SceneManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Custom Pointer");

    window.setMouseCursorVisible(false);

    SceneManager sceneManager;
    sceneManager.ClearScene();
    sceneManager.LoadSceneIsland();
    sceneManager.UpdateScene();

    return 0;
}
