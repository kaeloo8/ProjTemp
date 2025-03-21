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


    std::vector<std::string> AlreadyLoad;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::RectangleShape progressBarBg;
    sf::RectangleShape progressBar;

    int loadedImg = 0;
    int sizedirImg = 0;

    int sizedir = 0;
    int loaded = 0;
    float progress = 0.0f;

    sf::Texture& GetTexture(const std::string& path);
    void updateProgressBar();
    void parseTileMap(const std::string& chemin, const std::string& filename);
    void LoadFromFile(std::vector<std::string>);
    void LoadFromFile(std::string path);
};
