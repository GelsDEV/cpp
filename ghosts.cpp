#include "ghost_base.h"
#include "game_state.h"  // Für Zugriff auf Maze & Player & andere Definitionen
#include <cmath>         // Für std::abs

// Animatronics-Geist: Bleibt an seiner Position
class GhostAnimatronic : public GhostBase {
public:
    GhostAnimatronic(int row, int col)
        : GhostBase(row, col, GhostType::ANIMATRONIC) {}

    void move(GameState& /*state*/) override
    {
        // Keine Bewegung
    }
};

// Bowie-Geist: bewegt sich zunächst nach links, bis er nicht weiterkommt.
// Dann wechselt er die Richtung. Wenn beide Richtungen blockiert sind, bleibt er stehen.
class GhostBowie : public GhostBase {
private:
    bool movingLeft_ = true; // Bowies starten nach links
public:
    GhostBowie(int row, int col)
        : GhostBase(row, col, GhostType::BOWIE) {}

    void move(GameState& state) override
    {
        int nextCol = movingLeft_ ? col_ - 1 : col_ + 1;
        if (canMoveTo(row_, nextCol, state)) {
            col_ = nextCol;
        } else {
            // Richtung umkehren
            movingLeft_ = !movingLeft_;
            nextCol = movingLeft_ ? col_ - 1 : col_ + 1;
            // Prüfen, ob in die andere Richtung Bewegung möglich ist
            if (canMoveTo(row_, nextCol, state)) {
                col_ = nextCol;
            }
        }
    }

private:
    // Überprüft, ob das Feld begehbar ist
    bool canMoveTo(int r, int c, const GameState& state) const
    {
        if (r < 0 || r >= state.getMaze().getRows() ||
            c < 0 || c >= state.getMaze().getCols()) {
            return false;
        }

        char cell = state.getMaze().getCell(r, c);
        // Bowie-Geister behandeln '#' und 'T' als Hindernisse
        if (cell == '#' || cell == 'T') {
            return false;
        }
        return true;
    }
};

// Connelly-Geist: versucht aktiv, die SpielerIn zu fangen,
// indem er den größeren Abstand (Zeile oder Spalte) zuerst verringert.
class GhostConnelly : public GhostBase {
public:
    GhostConnelly(int row, int col)
        : GhostBase(row, col, GhostType::CONNELLY) {}

    void move(GameState& state) override
    {
        int playerRow = state.getPlayer().getPositionRow();
        int playerCol = state.getPlayer().getPositionCol();

        int dRow = playerRow - row_;
        int dCol = playerCol - col_;
        int absRow = std::abs(dRow);
        int absCol = std::abs(dCol);

        // Bestimmen, ob wir uns zuerst vertikal (Zeile) oder horizontal (Spalte) bewegen
        bool preferVertical = (absRow >= absCol);

        // Erster Versuch in der bevorzugten Richtung
        if (!moveInPreferredDirection(preferVertical, dRow, dCol, state)) {
            // Zweiter Versuch in der anderen Richtung
            moveInPreferredDirection(!preferVertical, dRow, dCol, state);
        }
    }

private:
    bool moveInPreferredDirection(bool vertical, int dRow, int dCol, GameState& state)
    {
        int nextRow = row_;
        int nextCol = col_;

        if (vertical) {
            // Einen Schritt in Richtung dRow
            if (dRow > 0)      nextRow = row_ + 1;
            else if (dRow < 0) nextRow = row_ - 1;
        } else {
            // Einen Schritt in Richtung dCol
            if (dCol > 0)      nextCol = col_ + 1;
            else if (dCol < 0) nextCol = col_ - 1;
        }

        if (canMoveTo(nextRow, nextCol, state)) {
            row_ = nextRow;
            col_ = nextCol;
            return true;
        }
        return false;
    }

    bool canMoveTo(int r, int c, const GameState& state) const
    {
        if (r < 0 || r >= state.getMaze().getRows() ||
            c < 0 || c >= state.getMaze().getCols()) {
            return false;
        }

        char cell = state.getMaze().getCell(r, c);
        // Connelly-Geister behandeln '#' und 'T' als unüberwindbare Hindernisse
        if (cell == '#' || cell == 'T') {
            return false;
        }
        return true;
    }
};

// Fabrikfunktion, die basierend auf einem Symbol den passenden Geist erzeugt
GhostBase* createGhost(int row, int col, char symbol)
{
    switch (symbol) {
    case 'A': // Animatronic
        return new GhostAnimatronic(row, col);
    case 'B': // Bowie
        return new GhostBowie(row, col);
    case 'C': // Connelly
        return new GhostConnelly(row, col);
    default:
        return nullptr; // Oder eine Exception auslösen
    }
}