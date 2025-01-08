#include "steps_to_goal.h"

// Rekursive Berechnung der kleinsten Schrittanzahl zum Ziel. Gibt INF_STEPS zurück, falls unerreichbar.
int computeStepsToGoal(const Maze& maze, int row, int col, int maxDepth,
                       int goalRow, int goalCol)
{
    // Position außerhalb des Labyrinths oder nicht begehbar => INF
    if (row < 0 || row >= maze.getRows() ||
        col < 0 || col >= maze.getCols()) {
        return INF_STEPS;
    }

    char cell = maze.getCell(row, col);
    // '#' oder 'T' behandeln wir als unpassierbar für diese Entfernungsberechnung
    if (cell == '#' || cell == 'T') {
        return INF_STEPS;
    }

    // Wenn wir das Ziel erreicht haben
    if (row == goalRow && col == goalCol) {
        return 0;
    }

    // Wenn die Suchtiefe aufgebraucht ist
    if (maxDepth == 0) {
        return INF_STEPS;
    }

    // Rekursiv die Nachbarn untersuchen (oben, unten, links, rechts)
    int oben    = computeStepsToGoal(maze, row - 1, col, maxDepth - 1, goalRow, goalCol);
    int unten   = computeStepsToGoal(maze, row + 1, col, maxDepth - 1, goalRow, goalCol);
    int links   = computeStepsToGoal(maze, row, col - 1, maxDepth - 1, goalRow, goalCol);
    int rechts  = computeStepsToGoal(maze, row, col + 1, maxDepth - 1, goalRow, goalCol);

    int minSteps = oben;
    if (unten < minSteps)   minSteps = unten;
    if (links < minSteps)   minSteps = links;
    if (rechts < minSteps)  minSteps = rechts;

    if (minSteps == INF_STEPS) {
        return INF_STEPS;
    }
    return 1 + minSteps;
}