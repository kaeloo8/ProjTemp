#include "pch.h"
#include "Ui.h"

Ui::Ui(const sf::Vector2u& windowSize) : menuVisible(false) {
    setupMenu(windowSize);
}

void Ui::setupMenu(const sf::Vector2u& windowSize) {
    // Définir la taille du menu en pourcentage de la fenêtre
    sf::Vector2f menuSize(windowSize.x * 0.5f, windowSize.y * 0.5f);
    menuBackground.setSize(menuSize);
    menuBackground.setFillColor(sf::Color(50, 50, 50, 200));
    menuBackground.setPosition(
        (windowSize.x - menuSize.x) / 2.f,
        (windowSize.y - menuSize.y) / 2.f
    );

    // Configuration du bouton de fermeture (taille relative au menu)
    sf::Vector2f buttonSize(menuSize.x * 0.075f, menuSize.y * 0.15f);
    closeButton.setSize(buttonSize);
    closeButton.setFillColor(sf::Color::Red);
    // Positionné en haut à droite du menu avec une marge (calculée en fonction du menu)
    closeButton.setPosition(
        menuBackground.getPosition().x + menuSize.x - buttonSize.x - 10.f,
        menuBackground.getPosition().y + 10.f
    );

    // Charger une police (vérifie que le chemin est correct)
    if (!font.loadFromFile("../../../res/DePixelHalbfett.ttf")) {
        std::cerr << "Erreur de chargement de la police!\n";
    }
    closeButtonText.setFont(font);
    closeButtonText.setString("X");
    // Taille du texte relative à la taille du bouton
    closeButtonText.setCharacterSize(static_cast<unsigned int>(buttonSize.y * 0.8f));
    closeButtonText.setFillColor(sf::Color::White);

    // Centrage du texte dans le bouton
    sf::FloatRect textBounds = closeButtonText.getLocalBounds();
    closeButtonText.setPosition(
        closeButton.getPosition().x + (buttonSize.x - textBounds.width) / 2.f - textBounds.left,
        closeButton.getPosition().y + (buttonSize.y - textBounds.height) / 2.f - textBounds.top
    );
}

void Ui::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    // Ouvrir le menu avec la touche Escape
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        menuVisible = true;
    }

    // Si le menu est visible, vérifier les clics sur le bouton de fermeture
    if (menuVisible) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (closeButton.getGlobalBounds().contains(mousePosF)) {
                menuVisible = false;
            }
        }
    }

    // Gérer le redimensionnement de la fenêtre
    if (event.type == sf::Event::Resized) {
        // Mettre à jour le layout en fonction de la nouvelle taille de la fenêtre
        updateLayout(sf::Vector2u(event.size.width, event.size.height));
    }
}

void Ui::update() {
    // Ici, on peut animer les éléments UI si nécessaire
}

void Ui::render(sf::RenderWindow& window) {
    if (menuVisible) {
        window.draw(menuBackground);
        window.draw(closeButton);
        window.draw(closeButtonText);
    }
}

bool Ui::isMenuVisible() const {
    return menuVisible;
}

void Ui::updateLayout(const sf::Vector2u& windowSize) {
    // Reconfigurer l'interface en fonction de la nouvelle taille
    setupMenu(windowSize);
}
