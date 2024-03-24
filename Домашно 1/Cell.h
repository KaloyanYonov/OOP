#pragma once

const int MAX_CELL_LENGTH = 50;

class Cell {
public:
    char data[MAX_CELL_LENGTH + 1];

    Cell();
    void clear();
};