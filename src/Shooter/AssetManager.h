#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class AssetManager {
public:
    std::vector<std::pair<std::string, sf::Texture>> images;
    std::vector<std::pair<std::string, std::unique_ptr<sf::Music>>> music;
    std::vector<std::pair<std::string, sf::SoundBuffer>> son;

    AssetManager();

    sf::Texture& GetTexture(const std::string& path);
    sf::SoundBuffer& GetSound(const std::string& path);
    sf::Music& GetMusic(const std::string& path);
};

#endif // ASSETMANAGER_H