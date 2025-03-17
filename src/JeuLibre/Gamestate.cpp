#include "pch.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "Gamestate.h"

GameState& GameState::getInstance() {
    static GameState instance;
    return instance;
}

void GameState::setPlayerName(const std::string& newName) {
    playerName = newName;
}

void GameState::addPlant(const std::string& plantName, float growthTime) {
    plantGrowth[plantName] = growthTime;
}

void GameState::updatePlantGrowth(const std::string& plantName, float timePassed) {
    if (plantGrowth.find(plantName) != plantGrowth.end()) {
        plantGrowth[plantName] += timePassed;
    }
}

float GameState::getPlantGrowth(const std::string& plantName) const {
    auto it = plantGrowth.find(plantName);
    return (it != plantGrowth.end()) ? it->second : 0.0f;
}
