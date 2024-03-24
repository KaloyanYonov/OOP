#include "Row.h"
#include <cstring>
#pragma warning (disable:4996)


Row::Row() : cellCount(0) {}

void Row::addCell(const char* v) {
    if (cellCount < MAX_CELLS) {
        strncpy(cells[cellCount].data, v, MAX_CELL_LENGTH);
        cells[cellCount].data[MAX_CELL_LENGTH] = '\0';
        ++cellCount;
    }
}

void Row::clear() {
    for (int i = 0; i < MAX_CELLS; ++i) {
        cells[i].clear();
    }
    cellCount = 0;
}
