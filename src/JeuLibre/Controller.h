#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Window.hpp>
#include <unordered_map>

// Définition des actions du jeu
enum class Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    // Vous pouvez ajouter d'autres actions (saut, attaque, etc.)
};

class Controller {
public:
    Controller();

    // Traite les événements SFML pour mettre à jour l'état des actions
    void handleEvent(const sf::Event& event);

    // Mise à jour en temps réel (utile pour vérifier l'état continu des touches)
    void update();

    // Vérifie si une action est actuellement active
    bool isActionActive(Action action) const;

private:
    // Stocke l'état (actif/inactif) de chaque action
    std::unordered_map<Action, bool> actionStates_;

    // Associe une touche SFML à une action
    std::unordered_map<sf::Keyboard::Key, Action> keyBindings_;
};

#endif // CONTROLLER_H
