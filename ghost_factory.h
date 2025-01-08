#pragma once

// Vorwärtsdeklaration der Fabrikfunktion, damit andere Dateien sie nutzen können
class GhostBase;

GhostBase* createGhost(int row, int col, char symbol);