#ifndef FIELD_H
#define FIELD_H

#include "Cell.h"
#include <vector>
#include <utility>

class Field {
private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> cells;
    int totalBombs;
    int openedCells;

    void expandEmptyArea(int row, int col);

public:
    Field(int numRows, int numCols, int bombs);

    void placeBombs();
    void calculateBombsNearby();
    bool openCell(int row, int col);
    void flagCell(int row, int col);
    bool checkWin() const;
    void displayField(bool showBombs) const;

    std::pair<int, int> autoplaySelectCell();
    void autoplay();
};

#endif // FIELD_H
