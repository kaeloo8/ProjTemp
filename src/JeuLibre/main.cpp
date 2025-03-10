#include "pch.h"
#include <SFML/Graphics.hpp>
#include "assetmanager.h"
#include "SceneManager.h"
#include "Vector2f.h"
#include <iostream>

int main() {
    Vector2f vect(10, 20);

    std::cout << vect.GetVect2f().x << " - " << vect.GetVect2f().y << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Custom Pointer");

    window.setMouseCursorVisible(false);

    SceneManager sceneManager;
    sceneManager.ClearScene();
    sceneManager.LoadSceneIsland();
    sceneManager.UpdateScene();

    return 0;
}
