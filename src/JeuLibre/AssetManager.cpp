#include "pch.h"
#include "AssetManager.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <memory>

AssetManager::AssetManager() {

}

AssetManager::AssetManager(sf::RenderWindow* W) {

    Win = W;

    std::string dossier = "../../../img/";
    int sizedir=0;

    progressBarBg.setSize(sf::Vector2f(Win->getSize().x / 2, Win->getSize().y / 15));
    progressBarBg.setFillColor(sf::Color(100, 100, 100));
    progressBarBg.setPosition((Win->getSize().x / 2) - (progressBarBg.getSize().x / 2),
        (Win->getSize().y / 2) - (progressBarBg.getSize().y / 2));

    progressBar.setSize(sf::Vector2f(0.f, progressBarBg.getSize().y));
    progressBar.setFillColor(sf::Color(0, 255, 0));
    progressBar.setPosition(progressBarBg.getPosition());

    for (const auto& entry : std::filesystem::directory_iterator(dossier)) {
        sizedir++;
    }

    for (const auto& entry : std::filesystem::directory_iterator(dossier)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
            std::string chemin = entry.path().string();
            std::string nom = entry.path().stem().string();
            sf::Texture texture;
            if (texture.loadFromFile(chemin)) {
                images.push_back({ nom, texture });
                std::cout << "Image chargée : " << nom << std::endl;
            }
            else {
                std::cerr << "Erreur : Impossible de charger l'image " << chemin << std::endl;
            }
        }

        loaded++;
        progress = static_cast<float>(loaded) / sizedir;
        progressBar.setSize(sf::Vector2f((Win->getSize().x / 2) * progress, progressBarBg.getSize().y));

        Win->clear();
        Win->draw(progressBarBg);
        Win->draw(progressBar);
        Win->display();
    }

    
}

sf::Texture& AssetManager::GetTexture(const std::string& path) {
    for (auto& pair : images) {
        if (pair.first == path) {
            return pair.second;
        }
    }
    throw std::runtime_error("Texture introuvable : " + path);
}
