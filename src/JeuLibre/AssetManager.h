#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

class AssetManager {

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
	std::vector< std::string> DosierListe ;
    std::vector<std::pair<std::string, sf::Texture>> images;
    sf::RenderWindow* Win;

    float progress = 0.f;
    size_t loaded = 0;
    sf::RectangleShape progressBarBg;
    sf::RectangleShape progressBar;

    AssetManager();
    AssetManager(sf::RenderWindow* W);
    
    sf::Texture& GetTexture(const std::string& path);
};

