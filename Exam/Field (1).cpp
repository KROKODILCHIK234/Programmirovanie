#include "Field.h"
#include <iostream>
#include <random>

Field::Field(int numRows, int numCols, int bombs) : rows(numRows), cols(numCols), totalBombs(bombs), openedCells(0) {
    cells.resize(rows, std::vector<Cell>(cols));
}

void Field::placeBombs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> randomRow(0, rows - 1);
    std::uniform_int_distribution<int> randomCol(0, cols - 1);

    int bombsPlaced = 0;
    while (bombsPlaced < totalBombs) {
        int bombRow = randomRow(gen);
        int bombCol = randomCol(gen);
        if (!cells[bombRow][bombCol].getBomb()) {
            cells[bombRow][bombCol].setBomb();
            ++bombsPlaced;
        }
    }
}

void Field::calculateBombsNearby() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j].getBomb()) {
                continue;
            }
            int bombsNearby = 0;
            for (int row = std::max(0, i - 1); row <= std::min(rows - 1, i + 1); ++row) {
                for (int col = std::max(0, j - 1); col <= std::min(cols - 1, j + 1); ++col) {
                    if (cells[row][col].getBomb()) {
                        ++bombsNearby;
                    }
                }
            }
            cells[i][j].setBombsNearby(bombsNearby);
        }
    }
}

bool Field::openCell(int row, int col) {
    if (cells[row][col].getFlagged()) {
        std::cout << "Cell is flagged. Unflag it before opening." << std::endl;
        return true;
    }
    if (cells[row][col].getOpen()) {
        std::cout << "Cell is already open." << std::endl;
        return true;
    }
    if (cells[row][col].getBomb()) {
        cells[row][col].setOpen();
        return false;
    }

    expandEmptyArea(row, col);
    return true;
}

void Field::flagCell(int row, int col) {
    if (cells[row][col].getOpen()) {
        std::cout << "Cannot flag an open cell." << std::endl;
        return;
    }
    cells[row][col].setFlagged(!cells[row][col].getFlagged());
}

bool Field::checkWin() const {
    return openedCells == (rows * cols - totalBombs);
}

void Field::displayField(bool showBombs) const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j].getOpen()) {
                if (cells[i][j].getBomb()) {
                    std::cout << "* ";
                }
                else {
                    std::cout << cells[i][j].getBombsNearby() << " ";
                }
            }
            else {
                if (cells[i][j].getFlagged()) {
                    std::cout << "* ";
                }
                else if (showBombs && cells[i][j].getBomb()) {
                    std::cout << "* ";
                }
                else {
                    std::cout << ". ";
                }
            }
        }
        std::cout << std::endl;
    }
}

void Field::expandEmptyArea(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || cells[row][col].getOpen() || cells[row][col].getBomb()) {
        return;
    }

    cells[row][col].setOpen();
    ++openedCells;

    if (cells[row][col].getBombsNearby() == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i != 0 || j != 0) {
                    expandEmptyArea(row + i, col + j);
                }
            }
        }
    }
}
