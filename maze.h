#pragma once
#include <vector>
#include <string>

class Maze {
private:
    int rows_;
    int cols_;
    std::vector<std::vector<char>> data_; // Enthält die Labyrinth-Daten

public:
    Maze(int rows, int cols, std::vector<std::vector<char>> data)
        : rows_(rows), cols_(cols), data_(std::move(data)) {}

    int getRows() const { return rows_; }
    int getCols() const { return cols_; }

    // “Getter” für den Inhalt einer Zelle
    char getCell(int r, int c) const {
        return data_[r][c];
    }

    // “Setter” für den Inhalt einer Zelle
    void setCell(int r, int c, char ch) {
        data_[r][c] = ch;
    }
};