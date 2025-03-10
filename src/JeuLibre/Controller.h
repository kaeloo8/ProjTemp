#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Window.hpp>
#include <unordered_map>

// D�finition des actions du jeu
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

    // Traite les �v�nements SFML pour mettre � jour l'�tat des actions
    void handleEvent(const sf::Event& event);

    // Mise � jour en temps r�el (utile pour v�rifier l'�tat continu des touches)
    void update();

    // V�rifie si une action est actuellement active
    bool isActionActive(Action action) const;

private:
    // Stocke l'�tat (actif/inactif) de chaque action
    std::unordered_map<Action, bool> actionStates_;

    // Associe une touche SFML � une action
    std::unordered_map<sf::Keyboard::Key, Action> keyBindings_;
};

#endif // CONTROLLER_H
