#include <iostream>
#include <fstream>
#include <cstring>
#include "MultiSet.h"

#pragma warning (disable : 4996)


int main() {
    size_t maxValue, k;
    std::cout << "Enter maximum value and bits per count: ";
    std::cin >> maxValue >> k;

    MultiSet ms(maxValue, k);
    MultiSet second(maxValue, k);

    std::cout << "Welcome to my MultiSet. Please select an option: " << std::endl;
    std::cout << "1. Add number (in the main set)" << std::endl;
    std::cout << "2. Count occurrences of number (in the main set)" << std::endl;
    std::cout << "3. Print (main set)" << std::endl;
    std::cout << "4. Memory representation (main set)" << std::endl;
    std::cout << "5. Serialization" << std::endl;
    std::cout << "6. Deserialization" << std::endl;
    std::cout << "7. Change maxValue (main set). Warning (this will delete all previous info" << std::endl;
    std::cout << "8. Change maxCount (main set)" << std::endl;
    std::cout << "9. Get maxValue and maxCount" << std::endl;
    std::cout << "10. Add number to the second set" << std::endl;
    std::cout << "11. Intersect with second set" << std::endl;
    std::cout << "12. Difference from second set" << std::endl;
    std::cout << "13. Complement (main set)" << std::endl;
    std::cout << "14. Exit" << std::endl;

    char filename[256];
    bool flag = false;
    while (!flag) {
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int num;
            std::cout << "Which number do you want to add in the main set? :  ";
            std::cin >> num;
            if (num > ms.getMaxValue()) {
                std::cout << "Invalid number!" << std::endl;
            }
            else {
                ms.add(num);
            }
            break;
        }
        case 2: {
            size_t num;
            std::cout << "Count of number? : ";
            std::cin >> num;
            std::cout << num << " is seen " << ms.count(num) << " " << "times in the set" << std::endl;
            break;
        }
        case 3:
            ms.print();
            break;
        case 4:
            ms.printMemory();
            break;
        case 5:
            std::cout << "Filename for serialization: ";
            std::cin >> filename;
            ms.serialization(filename);
            std::cout << "Serialization successful!" << std::endl;
            break;
        case 6:
            std::cout << "Filename for deserialization: ";
            std::cin >> filename;
            ms.deserialization(filename);
            std::cout << "Desireliazation successful!" << std::endl;
            break;
        case 7: {
            size_t newMaxValue;
            std::cout << "New maximum value: ";
            std::cin >> newMaxValue;
            ms.setMaxValue(newMaxValue);
            break;
        }
        case 8: {
            size_t newK;
            std::cout << "New max bits per count: ";
            std::cin >> newK;
            ms.setMaxCount(newK);
            break;
        }
        case 9:
            std::cout << "Current maximum value: " << ms.getMaxValue() << std::endl;
            std::cout << "Current maximum count: " << ms.getMaxCount() << " " << "HINT : (2^k - 1)" << std::endl;
            break;
        case 10: {
            int num;
            std::cout << "Add number to the second set: ";
            std::cin >> num;
            if (num > second.getMaxValue()) {
                std::cout << "Invalid number!" << std::endl;
            }
            else {
                second.add(num);
            }
            break;
        }
        case 11: {
            std::cout << "Intersection: " << std::endl;
            MultiSet intersection = ms.intersect(second);
            intersection.print();
            break;
        }
        case 12: {
            std::cout << "Difference: " << std::endl;
            MultiSet difference = ms.difference(second);
            difference.print();
            break;
        }
        case 13: {
            std::cout << "Complement: " << std::endl;
            MultiSet complement = ms.complement();
            complement.print();
            break;
        }
        case 14:
            flag = true;
            break;
        default:
            std::cout << "Something went wrong, tr y again" << std::endl;
        }
    }

    return 0;
}
