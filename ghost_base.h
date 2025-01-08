#pragma once
#include <vector>

// Vorwärtsdeklaration, um Kreisabhängigkeiten zu vermeiden
class GameState;

// Aufzählungstyp für die verschiedenen Geist-Arten
enum class GhostType {
    ANIMATRONIC,  // Bleibt an derselben Stelle
    BOWIE,        // Bewegt sich horizontal (links-rechts)
    CONNELLY      // Versucht, die SpielerIn zu verfolgen
};

// Basisklasse für alle Geister
class GhostBase {
protected:
    int row_;
    int col_;
    GhostType type_;

public:
    GhostBase(int row, int col, GhostType type)
        : row_(row), col_(col), type_(type) {}

    virtual ~GhostBase() = default;
    
    // Getter-Methoden
    int getRow() const { return row_; }
    int getCol() const { return col_; }
    GhostType getType() const { return type_; }

    // Wird nach jeder erfolgreichen Bewegung der SpielerIn aufgerufen,
    // damit der Geist sich aktualisieren kann.
    virtual void move(GameState& state) = 0;
};