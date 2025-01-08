#include <iostream>
#include <memory>
#include "maze.h"
#include "player.h"
#include "game_state.h"
#include "ghost_base.h"
#include "ghost_factory.h"
#include "steps_to_goal.h"

// ---------------------------------------------------------------------------
// Hilfsfunktionen
// ---------------------------------------------------------------------------

// Bewegt die Spielerfigur entsprechend der Eingabe ('w', 'a', 's', 'd')
void movePlayer(GameState& state, char direction) {
    // Aktuelle Position ermitteln
    int r = state.getPlayer().getPositionRow();
    int c = state.getPlayer().getPositionCol();

    // Neue Zielkoordinaten
    int newR = r;
    int newC = c;

    // Richtung auswerten
    switch (direction) {
        case 'w': // Aufwärts
            newR--;
            break;
        case 's': // Abwärts
            newR++;
            break;
        case 'a': // Links
            newC--;
            break;
        case 'd': // Rechts
            newC++;
            break;
        default:
            // Unerwartetes Kommando => keine Bewegung
            return;
    }

    // Zelleninhalt prüfen
    const Maze& maze = state.getMaze();
    if (newR < 0 || newR >= maze.getRows() ||
        newC < 0 || newC >= maze.getCols()) {
        // Außerhalb des Labyrinths -> Bewegung ignorieren
        return;
    }

    char cell = maze.getCell(newR, newC);
    // Hier kann man definieren, welche Felder begehbar sind.
    // Bsp.: '.', 'K', 'Z', 'A' -> begehbar
    // 'T' (Tür) ist nur begehbar, wenn man Schlüssel hat, usw.
    // Für den Einstieg behandeln wir '#' und 'T' als Hindernisse.
    if (cell == '#' || cell == 'T') {
        // Bewegung blockiert
        return;
    }

    // Bewegung durchführen
    state.getPlayer().setPosition(newR, newC);
}

// Prüft, ob die Spielerfigur auf einem Geist-Feld steht
bool checkGhostCollision(GameState& state) {
    int pRow = state.getPlayer().getPositionRow();
    int pCol = state.getPlayer().getPositionCol();

    for (auto& ghost : state.getGhosts()) {
        if (ghost->getRow() == pRow && ghost->getCol() == pCol) {
            return true;
        }
    }
    return false;
}

// Gibt das Labyrinth zusammen mit der Spielerposition und ggf. den Entfernungsinformationen aus
void displayMaze(const GameState& state) {
    const Maze& maze = state.getMaze();

    // Ziel in diesem Beispiel fix angenommen (z.B. [5,5]),
    // falls dein Code das Ziel woanders speichert, bitte anpassen
    int goalRow = 5;
    int goalCol = 5;

    // Im Info-Modus werden die Schritte bis zum Ziel berechnet (max. 5)
    if (state.isInfoMode()) {
        int steps = computeStepsToGoal(maze,
                                       state.getPlayer().getPositionRow(),
                                       state.getPlayer().getPositionCol(),
                                       5,
                                       goalRow, goalCol);
        if (steps <= 5) {
            std::cout << "(Schritte bis zum Ziel: " << steps << ")\n";
        }
    }

    // Labyrinth ausgeben
    int totalRows = maze.getRows();
    int totalCols = maze.getCols();

    for (int r = 0; r < totalRows; r++) {
        for (int c = 0; c < totalCols; c++) {
            // Prüfen, ob hier die Spielerfigur ist
            if (r == state.getPlayer().getPositionRow() &&
                c == state.getPlayer().getPositionCol()) {
                std::cout << 'S' << " ";
            } else {
                // Normales Labyrinth-Zeichen
                std::cout << maze.getCell(r, c) << " ";
            }
        }
        std::cout << "\n";
    }
}

// Gibt eine kurze Hilfe zu den Befehlen aus
void displayHelp() {
    std::cout << "Willkommen im Labyrinth!\n"
              << "Die moeglichen Befehle sind:\n"
              << "  w, a, s, d - Bewegung\n"
              << "  i - Informationsmodus umschalten\n"
              << "  h - Hilfe anzeigen\n"
              << "  q - Spiel beenden\n";
}

// Initialisiert Beispiel-Labyrinth mit Geistern
GameState initializeGame() {
    // Beispiel-Größe des Labyrinths
    int rows = 7;
    int cols = 7;
    std::vector<std::vector<char>> data(rows, std::vector<char>(cols, '.'));

    // Beispiel: Wände, Türen, Ziel
    data[1][2] = 'T';  // Tür
    data[2][3] = '#';  // Wand
    data[5][5] = 'Z';  // Ziel
    data[3][3] = 'C';  // Connelly-Geist
    data[4][1] = 'B';  // Bowie-Geist

    // Labyrinth-Objekt anlegen
    Maze maze(rows, cols, data);

    // Spielerfigur am Start (0,0)
    Player player(0, 0);

    // GameState erstellen
    GameState state(maze, player);

    // Geister finden und im State ablegen
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            char cell = data[r][c];
            if (cell == 'A' || cell == 'B' || cell == 'C') {
                // Geist erzeugen
                state.addGhost(std::unique_ptr<GhostBase>(createGhost(r, c, cell)));
                // Für die Anzeige als 'A' markieren
                state.getMaze().setCell(r, c, 'A');
            }
        }
    }
    return state;
}

// ---------------------------------------------------------------------------
// Hauptfunktion
// ---------------------------------------------------------------------------
int main() {
    try {
        // Spielzustand initialisieren
        GameState state = initializeGame();

        // Hauptschleife
        while (!state.getExit()) {
            // Aktuelles Labyrinth anzeigen
            displayMaze(state);

            // Prüfen, ob direkt zu Spielbeginn eventuell Kollisionen existieren
            if (checkGhostCollision(state)) {
                std::cout << "Sie haben einen Geist getroffen! Game Over!\n";
                break;
            }

            // Befehl lesen
            char cmd;
            std::cin >> cmd;
            if (!std::cin) {
                // Eingabe ungültig oder EOF -> raus aus Schleife
                break;
            }

            // Auswertung des Befehls
            switch (cmd) {
                case 'w':
                case 'a':
                case 's':
                case 'd':
                    // Spieler bewegen
                    movePlayer(state, cmd);

                    // Erneut auf Kollision prüfen
                    if (checkGhostCollision(state)) {
                        std::cout << "Sie haben einen Geist getroffen! Game Over!\n";
                        state.setExit(true);
                        break;
                    }

                    // Geister bewegen
                    for (auto& ghost : state.getGhosts()) {
                        ghost->move(state);
                    }

                    // Kollisionsprüfung nach Geisterbewegung
                    if (checkGhostCollision(state)) {
                        std::cout << "Sie haben einen Geist getroffen! Game Over!\n";
                        state.setExit(true);
                    }
                    break;

                case 'i':
                case 'I':
                    // Info-Modus umschalten
                    state.toggleInfoMode();
                    break;

                case 'h':
                case 'H':
                    displayHelp();
                    break;

                case 'q':
                case 'Q':
                    state.setExit(true);
                    break;

                default:
                    std::cout << "Unbekannter Befehl: " << cmd << "\n";
                    break;
            }
        }

        std::cout << "Spiel wird beendet. Schoenen Tag noch!\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
        return 1;
    }
}