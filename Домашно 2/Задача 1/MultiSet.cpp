#include "MultiSet.h"
#include <iostream>
#include <fstream>

MultiSet::MultiSet(size_t n, size_t k) : 
    maxValue(n), maxCount((1 << k) - 1), data(new unsigned char[n + 1]{}) {}

MultiSet::~MultiSet() {
    free();
}

MultiSet::MultiSet(const MultiSet& other) {
    copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MultiSet::MultiSet(MultiSet&& other) noexcept : data(nullptr), maxValue(0), maxCount(0) {
    *this = std::move(other);
}

MultiSet& MultiSet::operator=(MultiSet&& other) noexcept {
    if (this != &other) {
        free();
        maxValue = other.maxValue;
        maxCount = other.maxCount;
        data = other.data;
        other.data = nullptr;
    }
    return *this;
}

void MultiSet::free() {
    delete[] data;
    data = nullptr;
}

void MultiSet::copyFrom(const MultiSet& other) {
    data = new unsigned char[other.maxValue + 1];
    for (size_t i = 0; i <= other.maxValue; ++i) {
        data[i] = other.data[i];
    }
}

unsigned char MultiSet::min(unsigned char a, unsigned char b) const {
    return a < b ? a : b;
}

size_t MultiSet::findK(size_t maxCount) const {
    size_t k = 0;
    size_t count = 1;
    while (count - 1 < maxCount) {
        k++;
        count *= 2;
    }
    return k;
}

void MultiSet::add(size_t value) {
    if (value <= maxValue && data[value] < maxCount)
        data[value]++;
}

size_t MultiSet::count(size_t value) const {
    return value <= maxValue ? data[value] : 0;
}

void MultiSet::print() const {
    for (size_t i = 0; i <= maxValue; ++i)
        if (data[i] > 0)
            std::cout << i << ": " << (int)data[i] << std::endl;
}

void MultiSet::printMemory() const {
    std::cout << "Memory representation: ";
    for (size_t i = 0; i <= maxValue; ++i)
        std::cout << (size_t)data[i] << " ";
    std::cout << std::endl;
}

void MultiSet::serialization(const char* filename) {
    std::ofstream out(filename, std::ios::binary);
    out.write((char*)&maxValue, sizeof(maxValue));
    out.write((char*)&maxCount, sizeof(maxCount));
    out.write((char*)data, maxValue + 1);
    out.close();
}

void MultiSet::deserialization(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Unable to open file: ");
    }

    in.read((char*)&maxValue, sizeof(maxValue));
    in.read((char*)&maxCount, sizeof(maxCount));

    if (data != nullptr) {
        free();  
    }

    data = new unsigned char[maxValue + 1];
    in.read((char*)data, maxValue + 1);
    in.close();
}


size_t MultiSet::getMaxValue() const {
    return maxValue;
}

size_t MultiSet::getMaxCount() const {
    return maxCount;
}

void MultiSet::setMaxValue(int n) {
    if (n < 0) {
        throw std::invalid_argument("Maximum value must be greater than 0");
    }
    else {
        maxValue = n;
        delete[] data;
        data = new unsigned char[maxValue + 1]{};
    }
}

void MultiSet::setMaxCount(size_t k) {
    if (k < 1 || k > 8) {
        throw std::invalid_argument("Must be between 1 and 8");
    }
    else {
        maxCount = (1 << k) - 1;
    }

}

MultiSet MultiSet::intersect(const MultiSet& other) const {
    MultiSet result(maxValue, findK(maxCount));
    for (size_t i = 0; i <= maxValue; ++i) {
        result.data[i] = min(this->data[i], other.data[i]);
    }
    return result;
}

MultiSet MultiSet::difference(const MultiSet& other) const {
    MultiSet result(maxValue, findK(maxCount));
    for (size_t i = 0; i <= maxValue; ++i) {
        result.data[i] = this->data[i] > other.data[i] ? this->data[i] - other.data[i] : 0;
    }
    return result;
}

MultiSet MultiSet::complement() const {
    MultiSet result(maxValue, findK(maxCount));
    for (size_t i = 0; i <= maxValue; ++i) {
        result.data[i] = maxCount - this->data[i];
    }
    return result;
}
