#pragma once
#ifndef MODIFIABLE_INTEGERS_FUNCTION_H
#define MODIFIABLE_INTEGERS_FUNCTION_H

#include <fstream>

typedef int16_t(*funcPtr)(int16_t);

class ModifiableIntegersFunction {
private:
    static const int16_t MAX_VALUE = 32767;
    static const uint16_t MAX_RANGE = 65535;

    funcPtr lambda;
    int16_t* modifiedFunc;
    bool* definedFunc;
    void free();
    void copyFrom(const ModifiableIntegersFunction& other);

public:
    ModifiableIntegersFunction(funcPtr f);
    ~ModifiableIntegersFunction();
    ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
    ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
    void setModifiedOutput(int16_t input, int16_t output);
    void excludePoint(int16_t input);
    int16_t operator()(int16_t input) const;
    void serialization(const char* filename) const;
    void deserialization(const char* filename);
};

#endif
