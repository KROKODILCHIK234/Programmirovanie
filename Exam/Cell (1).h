#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool hasBomb;
    bool isOpen;
    bool isFlagged;
    int bombsNearby;

public:
    Cell();

    void setBomb();
    bool getBomb() const;

    void setOpen();
    bool getOpen() const;

    void setFlagged(bool flagged);
    bool getFlagged() const;

    void setBombsNearby(int bombs);
    int getBombsNearby() const;
};

#endif // CELL_H
