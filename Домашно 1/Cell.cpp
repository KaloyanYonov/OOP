#include "Cell.h"
#include <cstring>
#pragma warning (disable:4996)

Cell::Cell() {
    clear();
}

void Cell::clear() {
    memset(data, 0, sizeof(data));
}
