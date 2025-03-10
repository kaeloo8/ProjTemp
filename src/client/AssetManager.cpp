#include "pch.h"
#include "AssetManager.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <memory>

AssetManager::AssetManager() {

    std::string dossier = "../../../res/img/";

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
    }
    /*
    std::cout << "debut load son" << std::endl;

    std::string dossierSon = "../../src/son/";
    for (const auto& entry : std::filesystem::directory_iterator(dossierSon)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".mp3")) {
            std::string chemin = entry.path().string();
            std::string nom = entry.path().stem().string();

            sf::SoundBuffer buffer;
            if (buffer.loadFromFile(chemin)) {
                son.push_back({ nom, std::move(buffer) });
                std::cout << "Son chargé : " << nom << std::endl;
            }
            else {
                std::cerr << "Erreur : Impossible de charger le son " << chemin << std::endl;
            }
        }
    }*/

    std::cout << "debut load music" << std::endl;

    std::string dossierMusic = "../../../res/music/";
    for (const auto& entry : std::filesystem::directory_iterator(dossierMusic)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            std::string chemin = entry.path().string();
            std::string nom = entry.path().stem().string();
            std::unique_ptr<sf::Music> musique = std::make_unique<sf::Music>();
            if (musique->openFromFile(chemin)) {
                music.push_back({ nom, std::move(musique) });
                std::cout << "Musique chargée : " << nom << std::endl;
            }
            else {
                std::cerr << "Erreur : Impossible de charger la musique " << chemin << std::endl;
            }
        }
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

sf::SoundBuffer& AssetManager::GetSound(const std::string& path) {
    for (auto& pair : son) {
        if (pair.first == path) {
            return pair.second;
        }
    }
    throw std::runtime_error("Son introuvable : " + path);
}

sf::Music& AssetManager::GetMusic(const std::string& path) {
    for (auto& pair : music) {
        if (pair.first == path) {
            return *pair.second;
        }
    }
    throw std::runtime_error("Musique introuvable : " + path);
}