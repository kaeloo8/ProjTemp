#include "pch.h"
#include "assetmanager.h"
#include <iostream>

namespace fs = std::filesystem;

void AssetManager::loadTexturesFromFolder(const std::string& folderPath) {
    // Vérifie si le dossier existe
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Le dossier " << folderPath << " n'existe pas ou n'est pas un dossier.\n";
        return;
    }

    // Parcours tous les fichiers du dossier
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            std::string extension = entry.path().extension().string();

            // On peut filtrer par extension (ex: .png, .jpg, .jpeg, .bmp)
            if (extension == ".png" || extension == ".jpg" || extension == ".jpeg" || extension == ".bmp") {
                sf::Texture texture;
                if (texture.loadFromFile(path)) {
                    // On retire le dossier du chemin et on garde le nom du fichier
                    std::string filename = entry.path().filename().string();
                    textures_.emplace(filename, std::move(texture));
                    std::cout << "Texture chargee: " << filename << "\n";
                }
                else {
                    std::cerr << "Erreur de chargement de " << path << "\n";
                }
            }
        }
    }
}

const sf::Texture* AssetManager::getTexture(const std::string& name) const {
    auto it = textures_.find(name);
    if (it != textures_.end()) {
        return &it->second;
    }
    return nullptr;
}

void AssetManager::addTexture(const std::string& name, sf::Texture texture) {
    textures_.emplace(name, std::move(texture));
}
