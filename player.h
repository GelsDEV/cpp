#pragma once
#include <vector>

class Player {
private:
    int noKeys_;    // Anzahl an Schlüsseln
    int row_, col_; // Position der SpielerIn

public:
    Player(int row, int col)
        : noKeys_(0), row_(row), col_(col) {}

    int getKeys() const { return noKeys_; }
    void addKey() { noKeys_++; }
    void useKey() { if (noKeys_ > 0) noKeys_--; }

    int getPositionRow() const { return row_; }
    int getPositionCol() const { return col_; }
    
    void setPosition(int r, int c) {
        row_ = r;
        col_ = c;
    }
};