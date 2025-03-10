#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <filesystem>

class AssetManager {
public:
    void loadTexturesFromFolder(const std::string& folderPath);

    const sf::Texture* getTexture(const std::string& name) const;

    void addTexture(const std::string& name, sf::Texture texture);

private:
    std::unordered_map<std::string, sf::Texture> textures_;
};

#endif // ASSETMANAGER_H
