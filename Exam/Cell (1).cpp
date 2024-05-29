#include "Cell.h"

Cell::Cell() : hasBomb(false), isOpen(false), isFlagged(false), bombsNearby(0) {}

void Cell::setBomb() {
    hasBomb = true;
}

bool Cell::getBomb() const {
    return hasBomb;
}

void Cell::setOpen() {
    isOpen = true;
}

bool Cell::getOpen() const {
    return isOpen;
}

void Cell::setFlagged(bool flagged) {
    isFlagged = flagged;
}

bool Cell::getFlagged() const {
    return isFlagged;
}

void Cell::setBombsNearby(int bombs) {
    bombsNearby = bombs;
}

int Cell::getBombsNearby() const {
    return bombsNearby;
}
