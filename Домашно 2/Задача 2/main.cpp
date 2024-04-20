#include "ModifiableIntegersFunction.h"
#include <iostream>
#include <fstream>
#include <cstring>


//Cheat sheet : int16_t MAX VALUE = 32, 767->the maximum range is 65, 535


//Modifieable Integers Function is NOT fun !!!


int main() {
    auto f = [](int16_t x) -> int16_t { return x * 2; };
    ModifiableIntegersFunction func(f);

    int n;
    int16_t input, output;
    char filename[256];
    bool flag = false;

    std::cout << "1. Set a modifiable function" << std::endl;
    std::cout << "2. Exclude Point" << std::endl;
    std::cout << "3. Evaluate Function" << std::endl;
    std::cout << "4. Serialize" << std::endl;
    std::cout << "5. Deserialize" << std::endl;
    std::cout << "6. Exit" << std::endl;

    while (!flag) {
        std::cin >> n;

        switch (n) {
        case 1:
            std::cout << "Enter input and desired output: ";
            std::cin >> input >> output;
            func.setModifiedOutput(input, output);
            std::cout << "Modified output set for input " << input << " as " << output << std::endl;
            break;
        case 2:
            std::cout << "Enter exclude point : ";
            std::cin >> input;
            func.excludePoint(input);
            std::cout << "Point" << input << "excluded" << std::endl;
            break;
        case 3:
            std::cout << "Enter input to evaluate: ";
            std::cin >> input;
            try {
                output = func(input);
                std::cout << "Function value at " << input << " is " << output << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        case 4:
            std::cout << "Enter filename :";
            std::cin >> filename;
            try {
                func.serialization(filename);
                std::cout << "Serialization successful" << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        case 5:
            std::cout << "Enter filename :";
            std::cin >> filename;
            try {
                func.deserialization(filename);
                std::cout << "Deserialization successful " << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        case 6:
            flag = true;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
        }
    }

    return 0;
}

