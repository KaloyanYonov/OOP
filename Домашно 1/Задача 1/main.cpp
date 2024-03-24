#include <iostream>
#include <fstream>
#include <cstring>
#include "Table.h"

/*забележка : при изпълнение винаги на add трябва поредно да се добавят редовете(0 -> 1 -> 2 - > 3 и.т.н)
не знам дали трябваше да съобразя това, но не можах да го оправя.
*/

#pragma warning (disable:4996)


int main() {
    Table table;

    char filename[50];
    std::cout << "File name:";
    std::cin.getline(filename, 50);

    char command[7];
    while (true) {
        std::cout << "Choose : add,edit,remove or print ";
        std::cin >> command;

        
        if (strcmp(command, "add") == 0) {
            int row, valueCount;
            char value[MAX_CELL_LENGTH + 1];
            const char* values[MAX_CELLS];
            std::cout << "Enter row number and number of values: ";
            std::cin >> row >> valueCount;
            std::cin.ignore();

            for (int i = 0; i < valueCount; ++i) {
                std::cout << "Value " << i + 1 << ": ";
                std::cin.getline(value, MAX_CELL_LENGTH);
                values[i] = strdup(value); 
            }

            table.addRow(row, values, valueCount);
            for (int i = 0; i < valueCount; ++i) {
                free((void*)values[i]); 
            }
        }
        else if (strcmp(command, "edit") == 0) {
            int row, col;
            char newValue[MAX_CELL_LENGTH + 1];
            std::cout << "What Row ,Column , and value? ";
            std::cin >> row >> col;
            std::cin.ignore(); 
            std::cin.getline(newValue, MAX_CELL_LENGTH);

            table.editCell(row, col, newValue);
        }
        else if (strcmp(command, "remove") == 0) {
            int row;
            std::cout << "Row : ";
            std::cin >> row;

            table.removeRow(row);
        }
        else if (strcmp(command, "print") == 0) {
            table.print();
            table.saveToFile(filename);
            break;
        }
        else {
            std::cout << "Please choose a valid command!!!" << std::endl;
        }
    }

    return 0;
}