#include "Table.h"
#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

Table::Table() : RowCount(0) {}

void Table::addRow(int rowNumber, const char** values, int valueCount) {
    if (rowNumber >= 0 && rowNumber <= RowCount && RowCount < MAX_ROWS) {
        for (int i = RowCount; i > rowNumber; --i) {
            rows[i] = rows[i - 1];
        }
        rows[rowNumber].clear();
        for (int i = 0; i < valueCount; ++i) {
            rows[rowNumber].addCell(values[i]);
        }
        ++RowCount;
    }
}

void Table::removeRow(int rowNumber) {
    if (rowNumber >= 0 && rowNumber < RowCount) {
        for (int i = rowNumber; i < RowCount - 1; ++i) {
            rows[i] = rows[i + 1];
        }
        --RowCount;
        rows[RowCount].clear();
    }
}

void Table::editCell(int rowNumber, int colNumber, const char* newValue) {
    if (rowNumber >= 0 && rowNumber < RowCount && colNumber >= 0 && colNumber < MAX_CELLS) {
        strncpy(rows[rowNumber].cells[colNumber].data, newValue, MAX_CELL_LENGTH);
        rows[rowNumber].cells[colNumber].data[MAX_CELL_LENGTH] = '\0';
    }
}

void Table::print() {
    for (int i = 0; i < RowCount; ++i) {
        for (int j = 0; j < rows[i].cellCount; ++j) {
            std::cout << "|" << rows[i].cells[j].data;
        }
        std::cout << "|" << std::endl;
    }
}
void Table::saveToFile(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    file << "<table>" << std::endl;
    for (int i = 0; i < RowCount; ++i) {
        file << "<tr>" << std::endl;
        for (int j = 0; j < rows[i].cellCount; ++j) {
            file << "<td>" << rows[i].cells[j].data << "</td>" << std::endl;
        }
        file << "</tr>" << std::endl;
    }
    file << "</table>";
    file.close();
}
