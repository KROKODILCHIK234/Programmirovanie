#include <iostream>
#include <vector>
#include <random>

class Cell {
private:
    bool hasBomb;
    bool isOpen;
    bool isFlagged;
    int bombsNearby;
public:
    Cell() : hasBomb(false), isOpen(false), isFlagged(false), bombsNearby(0) {}

    void setBomb() {
        hasBomb = true;
    }

    bool getBomb() const {
        return hasBomb;
    }

    void setOpen() {
        isOpen = true;
    }

    bool getOpen() const {
        return isOpen;
    }

    void setFlagged(bool flagged) {
        isFlagged = flagged;
    }

    bool getFlagged() const {
        return isFlagged;
    }

    void setBombsNearby(int bombs) {
        bombsNearby = bombs;
    }

    int getBombsNearby() const {
        return bombsNearby;
    }
};

class Field {
private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> cells;
    int totalBombs;
    int openedCells;

    void expandEmptyArea(int row, int col) {
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

public:
    Field(int numRows, int numCols, int bombs) : rows(numRows), cols(numCols), totalBombs(bombs), openedCells(0) {
        cells.resize(rows, std::vector<Cell>(cols));
    }

    void placeBombs() {
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

    void calculateBombsNearby() {
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

    bool openCell(int row, int col) {
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

    void flagCell(int row, int col) {
        if (cells[row][col].getOpen()) {
            std::cout << "Cannot flag an open cell." << std::endl;
            return;
        }
        cells[row][col].setFlagged(!cells[row][col].getFlagged());
    }

    bool checkWin() const {
        return openedCells == (rows * cols - totalBombs);
    }

    void displayField(bool showBombs) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (cells[i][j].getOpen()) {
                    if (cells[i][j].getBomb()) {
                        std::cout << "* ";
                    } else {
                        std::cout << cells[i][j].getBombsNearby() << " ";
                    }
                } else {
                    if (cells[i][j].getFlagged()) {
                        std::cout << "* ";
                    } else if (showBombs && cells[i][j].getBomb()) {
                        std::cout << "* ";
                    } else {
                        std::cout << ". ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int rows, cols, numBombs;
    std::cout << "Enter number of rows, columns, and bombs: ";
    std::cin >> rows >> cols >> numBombs;

    if (numBombs >= rows * cols) {
        std::cerr << "Number of bombs should be less than the number of cells." << std::endl;
        return 1;
    }

    Field field(rows, cols, numBombs);
    field.placeBombs();
    field.calculateBombsNearby();

    bool gameOver = false;
    while (!gameOver) {
        field.displayField(false);

        char action;
        int selectedRow, selectedCol;
        std::cout << "Enter 'o' to open a cell or 'f' to flag/unflag a cell: ";
        std::cin >> action >> selectedRow >> selectedCol;

        if (selectedRow < 0 || selectedRow >= rows || selectedCol < 0 || selectedCol >= cols) {
            std::cerr << "Invalid cell position. Try again." << std::endl;
            continue;
        }

        if (action == 'o') {
            gameOver = !field.openCell(selectedRow, selectedCol);
        } else if (action == 'f') {
            field.flagCell(selectedRow, selectedCol);
        } else {
            std::cerr << "Invalid action. Use 'o' to open or 'f' to flag." << std::endl;
        }

        if (gameOver) {
            field.displayField(true);
            std::cout << "Game Over! You stepped on a bomb." << std::endl;
        } else if (field.checkWin()) {
            field.displayField(true);
            std::cout << "Congratulations! You've won the game!" << std::endl;
            gameOver = true;
        }
    }

    return 0;
}
