#pragma once
#include <vector>
#include <memory>
#include "maze.h"
#include "player.h"

class GhostBase; // Vorwärtsdeklaration

// Hält den kompletten Spielzustand
class GameState {
private:
    Maze maze_;
    Player player_;
    bool exit_ = false;     // Ob das Spiel beendet werden soll
    bool infoMode_ = false; // Ob der Informations-Modus aktiv ist

    // Container für alle Geister
    std::vector<std::unique_ptr<GhostBase>> ghosts_;

public:
    GameState(const Maze& maze, const Player& player)
        : maze_(maze), player_(player) {}

    Maze& getMaze() { return maze_; }
    const Maze& getMaze() const { return maze_; }

    Player& getPlayer() { return player_; }
    const Player& getPlayer() const { return player_; }

    void setExit(bool val) { exit_ = val; }
    bool getExit() const { return exit_; }

    void toggleInfoMode() { infoMode_ = !infoMode_; }
    bool isInfoMode() const { return infoMode_; }

    // Methoden zum Verwalten der Geister
    void addGhost(std::unique_ptr<GhostBase> g) {
        ghosts_.push_back(std::move(g));
    }

    std::vector<std::unique_ptr<GhostBase>>& getGhosts() {
        return ghosts_;
    }
};