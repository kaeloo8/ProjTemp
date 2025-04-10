#include "pch.h"
#include "AssetManager.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm> // pour std::find

AssetManager::AssetManager() {}

AssetManager::AssetManager(sf::RenderWindow* W) : Win(W) {
    std::vector<std::string> DosierListe = {
        "../../../img/",
        "../../../img/Player/",
        "../../../img/Hair/",
        "../../../img/Hand/",
        "../../../img/Farming/",
        "../../../img/Monster/",
        "../../../img/Ui/",
        "../../../img/MapTile/Donjon",
        "../../../img/MapTile/"
    };
    LoadFromFile(DosierListe);
}

void AssetManager::updateProgressBar() {
    progress = static_cast<float>(loadedImg) / sizedirImg;
    progressBar.setSize(sf::Vector2f((Win->getSize().x / 2) * progress, progressBarBg.getSize().y));

    Win->clear();
    Win->draw(backgroundSprite);
    Win->draw(progressBarBg);
    Win->draw(progressBar);
    Win->display();
}

void AssetManager::parseTileMap(const std::string& chemin, const std::string& filename) {
    std::vector<std::string> parts;
    std::stringstream ss(filename);
    std::string item;
    while (std::getline(ss, item, '_')) parts.push_back(item);

    if (parts.size() != 4) {
        std::cerr << "Erreur : Format incorrect pour la tilemap " << filename << std::endl;
        return;
    }

    int cols = std::stoi(parts[1]);
    int rows = std::stoi(parts[2]);
    std::string baseName = parts[3];

    sf::Texture fullTexture;
    if (!fullTexture.loadFromFile(chemin)) {
        std::cerr << "Erreur : Impossible de charger la tilemap " << chemin << std::endl;
        return;
    }

    sf::Image fullImage = fullTexture.copyToImage();
    int tileWidth = fullTexture.getSize().x / cols;
    int tileHeight = fullTexture.getSize().y / rows;

    int index = 0;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            sf::Texture tileTexture;
            tileTexture.loadFromImage(fullImage, sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));

            std::ostringstream formattedIndex;
            formattedIndex << std::setw(4) << std::setfill('0') << index;
            std::string tileName = baseName + "_" + formattedIndex.str();

            images.emplace_back(ImageData{ tileName, std::move(tileTexture) });

            ++index;
            ++loaded;
            ++loadedImg;

            if (loadedImg % 10 == 0 || loadedImg == sizedirImg) {
                updateProgressBar();
            }
        }
    }
}

sf::Texture& AssetManager::GetTexture(const std::string& path) {
    for (auto& pair : images) {
        if (pair.name == path) return pair.texture;
    }
    throw std::runtime_error("Texture introuvable : " + path);
}

void AssetManager::LoadFromFile(std::vector<std::string> DosierListe) {
    progress = 0.0f;
    sizedirImg = 0;
    loadedImg = 0;

    if (!backgroundTexture.loadFromFile("../../../img/LoadingScreen.png")) {
        std::cerr << "Erreur : Impossible de charger l'image de fond\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(Win->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(Win->getSize().y) / backgroundTexture.getSize().y
    );

    progressBarBg.setSize(sf::Vector2f(Win->getSize().x / 2, Win->getSize().y / 15));
    progressBarBg.setFillColor(sf::Color(30, 30, 30));
    progressBarBg.setPosition((Win->getSize().x / 2) - (progressBarBg.getSize().x / 2),
        (Win->getSize().y / 6 * 5) - (progressBarBg.getSize().y / 2));

    progressBar.setSize(sf::Vector2f(0.f, progressBarBg.getSize().y));
    progressBar.setFillColor(sf::Color(0, 0, 255));
    progressBar.setPosition(progressBarBg.getPosition());

    for (const auto& nDosier : DosierListe) {
        if (std::find(AlreadyLoad.begin(), AlreadyLoad.end(), nDosier) != AlreadyLoad.end()) continue;

        for (const auto& entry : std::filesystem::directory_iterator(nDosier)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::string filename = entry.path().stem().string();

                if (filename.rfind("CUT_", 0) == 0) {
                    std::vector<std::string> parts;
                    std::stringstream ss(filename);
                    std::string item;

                    while (std::getline(ss, item, '_')) parts.push_back(item);

                    if (parts.size() == 4) {
                        int cols = std::stoi(parts[1]);
                        int rows = std::stoi(parts[2]);
                        sizedir += cols * rows;
                        sizedirImg += cols * rows;
                    }
                    else {
                        ++sizedir;
                        ++sizedirImg;
                    }
                }
                else {
                    ++sizedir;
                    ++sizedirImg;
                }
            }
        }

        images.reserve(sizedirImg);

        for (const auto& entry : std::filesystem::directory_iterator(nDosier)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::string chemin = entry.path().string();
                std::string filename = entry.path().stem().string();

                if (filename.rfind("CUT_", 0) == 0) {
                    parseTileMap(chemin, filename);
                }
                else {
                    sf::Texture texture;
                    if (texture.loadFromFile(chemin)) {
                        images.emplace_back(ImageData{ filename, std::move(texture) });
                    }
                    else {
                        std::cerr << "Erreur : Impossible de charger l'image " << chemin << std::endl;
                    }
                    ++loaded;
                    ++loadedImg;
                    if (loadedImg % 10 == 0 || loadedImg == sizedirImg)
                        updateProgressBar();
                }
            }
        }

        AlreadyLoad.push_back(nDosier);
    }
}

void AssetManager::LoadFromFile(std::string path) {
    if (std::find(AlreadyLoad.begin(), AlreadyLoad.end(), path) != AlreadyLoad.end()) return;
    LoadFromFile(std::vector<std::string>{path});
}
