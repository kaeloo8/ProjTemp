#include "pch.h"
#include "assetmanager.h"
#include <iostream>

namespace fs = std::filesystem;


AssetManager::AssetManager() {
    return;
}

AssetManager::AssetManager(sf::RenderWindow* W) {
    if (W == nullptr) {
        std::cerr << "Erreur : la fenêtre (RenderWindow) est nulle !" << std::endl;
    }
    else {
        Win = W;
    }
}

void AssetManager::loadTexturesFromFolder(const std::string& _folderPath) {

    progressBarBg.setSize(sf::Vector2f(Win->getSize().x/2, Win->getSize().y / 15));
    progressBarBg.setFillColor(sf::Color(100, 100, 100));
    progressBarBg.setPosition((Win->getSize().x / 2) - (progressBarBg.getSize().x / 2), (Win->getSize().y / 2)- (progressBarBg.getSize().y / 2));

    progressBar.setSize(sf::Vector2f(0.f, 30.f));
    progressBar.setFillColor(sf::Color(0, 255, 0));
    progressBar.setPosition(progressBarBg.getPosition());

    std::string folderPath = _folderPath; 
    if (fs::exists(folderPath) && fs::is_directory(folderPath)) {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp") {
                    files.push_back(entry);
                }
            }
        }
    }

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
        Update();
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


void AssetManager::Update() {
    if (loaded < files.size()) {
        const auto& file = files[loaded];

        sf::Texture texture;
        if (texture.loadFromFile(file.path().string())) {
            std::string filename = file.path().filename().string();
            std::cerr << "Chargé : " << filename << "\n";
        }
        else {
            std::cerr << "Erreur lors du chargement de " << file.path().string() << "\n";
        }

        // Mise à jour de la barre de progression
        loaded++;
        progress = static_cast<float>(loaded) / files.size();

        // Mettre à jour la taille de la barre de progression en fonction de la progression
        progressBar.setSize(sf::Vector2f((Win->getSize().x / 2) * progress, progressBarBg.getSize().y));
    }

    // Dessiner la barre de progression uniquement si Win est valide
    if (Win != nullptr) {
        Win->clear();
        Win->draw(progressBarBg);
        Win->draw(progressBar);
        Win->display();
    }
    else {
        std::cerr << "Erreur : la fenêtre n'est pas initialisée." << std::endl;
    }
}
