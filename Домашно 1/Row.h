#pragma once
#include "Cell.h"

const int MAX_CELLS = 15;

class Row {
public:
    Cell cells[MAX_CELLS];
    int cellCount;

    Row();
    void addCell(const char* value);
    void clear();
};