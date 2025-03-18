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

    DosierListe.push_back("../../../img/");
    DosierListe.push_back("../../../img/Ui/");
    DosierListe.push_back("../../../img/Player/");
	DosierListe.push_back("../../../img/Hair/");
    DosierListe.push_back("../../../img/Hand/");
    DosierListe.push_back("../../../img/Monster/");
    int sizedir = 0;

    // Charger l’image de fond
    if (!backgroundTexture.loadFromFile("../../../img/LoadingScreen.png")) {
        std::cerr << "Erreur : Impossible de charger l'image de fond\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(Win->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(Win->getSize().y) / backgroundTexture.getSize().y
    );


    progressBarBg.setSize(sf::Vector2f(Win->getSize().x / 2, Win->getSize().y / 15));
    progressBarBg.setFillColor(sf::Color(30,30,30));
    progressBarBg.setPosition((Win->getSize().x / 2) - (progressBarBg.getSize().x / 2),
        (Win->getSize().y/6 *5 ) - (progressBarBg.getSize().y / 2));

    progressBar.setSize(sf::Vector2f(0.f, progressBarBg.getSize().y));
    progressBar.setFillColor(sf::Color(0, 0, 255));
    progressBar.setPosition(progressBarBg.getPosition());

    for (auto nDosier : DosierListe){
        for (const auto& entry : std::filesystem::directory_iterator(nDosier)) {
            sizedir++;
        }
    }

    for (auto nDosier : DosierListe) {
        for (const auto& entry : std::filesystem::directory_iterator(nDosier)) {
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
            Win->draw(backgroundSprite);
            Win->draw(progressBarBg);
            Win->draw(progressBar);
            Win->display();
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
