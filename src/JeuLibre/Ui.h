#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Ui {
public:
    Ui(const sf::Vector2u& windowSize);

    // Traite les �v�nements (touches, clics et redimensionnement)
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    // Mise � jour �ventuelle des �l�ments UI (pour les animations, par exemple)
    void update();

    // Affichage des �l�ments UI
    void render(sf::RenderWindow& window);

    // Indique si le menu est visible
    bool isMenuVisible() const;

    // Mise � jour du layout en fonction d'une nouvelle taille de fen�tre
    void updateLayout(const sf::Vector2u& windowSize);

private:
    bool menuVisible;

    // Fond du menu et bouton de fermeture
    sf::RectangleShape menuBackground;
    sf::RectangleShape closeButton;
    sf::Text closeButtonText;
    sf::Font font;

    // Initialise les �l�ments du menu avec la taille de la fen�tre
    void setupMenu(const sf::Vector2u& windowSize);
};

#endif // UI_H
