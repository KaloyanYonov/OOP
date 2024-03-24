#pragma once
#include "Row.h"

const int MAX_ROWS = 100;

class Table {
private:
    Row rows[MAX_ROWS];
    int RowCount;

public:
    Table();
    void addRow(int rowNumber, const char** values, int valueCount);
    void removeRow(int rowNumber);
    void editCell(int rowNumber, int colNumber, const char* newValue);
    void print();
    void saveToFile(const char* filename);
};