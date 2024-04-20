#include "ModifiableIntegersFunction.h"
#include <cstring>
#include <fstream>

ModifiableIntegersFunction::ModifiableIntegersFunction(funcPtr f) : lambda(f) {
    modifiedFunc = new int16_t[MAX_RANGE + 1];
    definedFunc = new bool[MAX_RANGE + 1];
    for (int i = 0; i <= MAX_RANGE; ++i) {
        modifiedFunc[i] = 0;
        definedFunc[i] = false;
    }
}

ModifiableIntegersFunction::~ModifiableIntegersFunction() {
    free();
}

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other) {
    copyFrom(other);
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

void ModifiableIntegersFunction::setModifiedOutput(int16_t input, int16_t output) {
    int index = input + MAX_VALUE + 1;
    modifiedFunc[index] = output;
    definedFunc[index] = true;
}

void ModifiableIntegersFunction::excludePoint(int16_t input) {
    definedFunc[input + MAX_VALUE + 1] = false;
}

int16_t ModifiableIntegersFunction::operator()(int16_t input) const {
    int index = input + MAX_VALUE + 1;
    if (!definedFunc[index]) {
        throw std::runtime_error("Attempt to access undefined point.");
    }
    return modifiedFunc[index] != 0 ? modifiedFunc[index] : lambda(input);
}

void ModifiableIntegersFunction::serialization(const char* filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for writing.");
    }
    file.write((const char*)modifiedFunc, sizeof(int16_t) * (MAX_RANGE + 1));
    file.write((const char*)definedFunc, sizeof(bool) * (MAX_RANGE + 1));
    file.close();
}

void ModifiableIntegersFunction::deserialization(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for reading.");
    }
    file.read((char*)modifiedFunc, sizeof(int16_t) * (MAX_RANGE + 1));
    file.read((char*)definedFunc, sizeof(bool) * (MAX_RANGE + 1));
    file.close();
}

void ModifiableIntegersFunction::free() {
    delete[] modifiedFunc;
    delete[] definedFunc;
}

void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other) {
    lambda = other.lambda;
    modifiedFunc = new int16_t[MAX_RANGE + 1];
    definedFunc = new bool[MAX_RANGE + 1];
    for (int i = 0; i <= MAX_RANGE; ++i) {
        modifiedFunc[i] = other.modifiedFunc[i];
        definedFunc[i] = other.definedFunc[i];
    }
}
