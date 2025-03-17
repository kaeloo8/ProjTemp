#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <unordered_map>
#include <vector>
#include <string>

class GameState {
public:
    static GameState& getInstance();

    void setPlayerName(const std::string& newName);
    void addPlant(const std::string& plantName, float growthTime);
    void updatePlantGrowth(const std::string& plantName, float timePassed);
    float getPlantGrowth(const std::string& plantName) const;

    std::string playerName;
    std::vector<std::string> inventory;
    std::unordered_map<std::string, float> plantGrowth;

private:
    GameState() = default;
};

#endif // GAME_STATE_H
