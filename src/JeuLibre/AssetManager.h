#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

class AssetManager {

    sf::RenderWindow* Win;
    std::unordered_map<std::string, sf::Texture> textures_;

    float progress = 0.f;
    std::vector<fs::directory_entry> files;
    size_t loaded = 0;
    sf::RectangleShape progressBarBg;
    sf::RectangleShape progressBar;
public:
    AssetManager();
    AssetManager(sf::RenderWindow* W);
    void loadTexturesFromFolder(const std::string& folderPath);

    const sf::Texture* getTexture(const std::string& name) const;

    void addTexture(const std::string& name, sf::Texture texture);

    void Update();
};

