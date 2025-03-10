#include "pch.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <iostream>
#include "assetmanager.h"
#include "Ui.h"

namespace fs = std::filesystem;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu SFML - Chargement, Curseur & UI");
    window.setFramerateLimit(60);

    // --- Ecran de chargement ---
    sf::RectangleShape progressBarBg(sf::Vector2f(400.f, 30.f));
    progressBarBg.setFillColor(sf::Color(100, 100, 100));
    progressBarBg.setPosition((800 - 400) / 2.f, (600 - 30) / 2.f);

    sf::RectangleShape progressBar(sf::Vector2f(0.f, 30.f));
    progressBar.setFillColor(sf::Color(0, 255, 0));
    progressBar.setPosition(progressBarBg.getPosition());

    // --- Chargement des assets ---
    AssetManager assetManager;
    std::string folderPath = "../../../img"; // Adapté à votre structure
    std::vector<fs::directory_entry> files;

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
    else {
        std::cerr << "Le dossier " << folderPath << " est introuvable!\n";
        return -1;
    }

    size_t total = files.size();
    size_t loaded = 0;

    // Chargement progressif avec barre de chargement
    for (const auto& file : files) {
        sf::Texture texture;
        if (texture.loadFromFile(file.path().string())) {
            std::string filename = file.path().filename().string();
            assetManager.addTexture(filename, std::move(texture));
            std::cout << "Chargé : " << filename << "\n";
        }
        else {
            std::cerr << "Erreur lors du chargement de " << file.path().string() << "\n";
        }
        loaded++;
        float progress = static_cast<float>(loaded) / total;
        progressBar.setSize(sf::Vector2f(400.f * progress, 30.f));

        window.clear();
        window.draw(progressBarBg);
        window.draw(progressBar);
        window.display();

        sf::sleep(sf::milliseconds(50)); // Pour visualiser la progression
    }

    window.setTitle("Chargement terminé");

    // --- Création du menu UI ---
    Ui ui(window.getSize());

    // --- Curseur personnalisé ---
    window.setMouseCursorVisible(false);
    const sf::Texture* pointerTexture = assetManager.getTexture("Pointer.png");
    if (!pointerTexture) {
        std::cerr << "La texture 'Pointer.png' est introuvable dans les assets!\n";
        return -1;
    }
    sf::Sprite pointerSprite(*pointerTexture);
    pointerSprite.setOrigin(0,0);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Transmet les événements à l'UI
            ui.handleEvent(event, window);

            // Si redimensionnement, mettre à jour la vue et le layout
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                ui.updateLayout(sf::Vector2u(event.size.width, event.size.height));
            }
        }

        ui.update();

        // Met à jour la position du curseur personnalisé
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        pointerSprite.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        pointerSprite.setScale(1.3, 1.3);
        window.clear(sf::Color::Black);
        // Ici, vous pouvez dessiner d'autres éléments du jeu...
        ui.render(window); // Dessine le menu si visible
        window.draw(pointerSprite); // Dessine le curseur personnalisé
        window.display();
    }

    return 0;
}
