#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

class AssetManager {
public:
    AssetManager();
    explicit AssetManager(sf::RenderWindow* W);
    struct ImageData {
        std::string name;
        sf::Texture texture;
    };

    sf::RenderWindow* Win;
    std::vector<ImageData> images;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::RectangleShape progressBarBg;
    sf::RectangleShape progressBar;

    int sizedir = 0;
    int loaded = 0;
    float progress = 0.0f;

    sf::Texture& GetTexture(const std::string& path);
    void updateProgressBar();
    void parseTileMap(const std::string& chemin, const std::string& filename);
};
