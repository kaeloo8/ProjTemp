#include "pch.h"
#include "Controller.h"

Controller::Controller() {
    // Initialisation des �tats d'action � false
    actionStates_[Action::MoveUp] = false;
    actionStates_[Action::MoveDown] = false;
    actionStates_[Action::MoveLeft] = false;
    actionStates_[Action::MoveRight] = false;

    // Configuration des touches par d�faut
    keyBindings_[sf::Keyboard::Up] = Action::MoveUp;
    keyBindings_[sf::Keyboard::Down] = Action::MoveDown;
    keyBindings_[sf::Keyboard::Left] = Action::MoveLeft;
    keyBindings_[sf::Keyboard::Right] = Action::MoveRight;
}

void Controller::handleEvent(const sf::Event& event) {
    // Gestion des �v�nements de type KeyPressed et KeyReleased
    if (event.type == sf::Event::KeyPressed) {
        auto it = keyBindings_.find(event.key.code);
        if (it != keyBindings_.end()) {
            actionStates_[it->second] = true;
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        auto it = keyBindings_.find(event.key.code);
        if (it != keyBindings_.end()) {
            actionStates_[it->second] = false;
        }
    }
}

void Controller::update() {
    // Mise � jour en temps r�el : on v�rifie l'�tat actuel de chaque touche li�e � une action
    for (const auto& binding : keyBindings_) {
        Action action = binding.second;
        if (sf::Keyboard::isKeyPressed(binding.first)) {
            actionStates_[action] = true;
        }
        else {
            actionStates_[action] = false;
        }
    }
}

bool Controller::isActionActive(Action action) const {
    auto it = actionStates_.find(action);
    return (it != actionStates_.end()) ? it->second : false;
}
