#include <iostream>
#include "Field.h"

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

    char choice;
    std::cout << "Do you want to watch the autoplay (a) or play manually (m)? ";
    std::cin >> choice;

    if (choice == 'a') {
        field.autoplay();
    }
    else if (choice == 'm') {
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
            }
            else if (action == 'f') {
                field.flagCell(selectedRow, selectedCol);
            }
            else {
                std::cerr << "Invalid action. Use 'o' to open or 'f' to flag." << std::endl;
            }

            if (gameOver) {
                field.displayField(true);
                std::cout << "Game Over! You stepped on a bomb." << std::endl;
            }
            else if (field.checkWin()) {
                field.displayField(true);
                std::cout << "Congratulations! You've won the game!" << std::endl;
                gameOver = true;
            }
        }
    }
    else {
        std::cerr << "Invalid choice. Exiting..." << std::endl;
        return 1;
    }

    return 0;
}
