#pragma once
#include "maze.h"

// Konstante, um "unendlich viele Schritte" zu repräsentieren
constexpr int INF_STEPS = 99999;

// Rekursive Funktion zur Berechnung der Schritte zum Ziel (maximal 5 Tiefe)
int computeStepsToGoal(const Maze& maze, int row, int col, int maxDepth,
                       int goalRow, int goalCol);