#pragma once
#ifndef MULTISET_H
#define MULTISET_H

#include <fstream>

class MultiSet {
private:
    size_t maxValue;
    size_t maxCount;
    unsigned char* data;

    void free();
    void copyFrom(const MultiSet& other);
   
    unsigned char min(unsigned char a, unsigned char b) const;
    size_t findK(size_t maxCount) const;

public:
    MultiSet(size_t n, size_t k);
    ~MultiSet();
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    MultiSet(MultiSet&& other) noexcept;
    MultiSet& operator=(MultiSet&& other) noexcept;
    void add(size_t value);
    size_t count(size_t value) const;
    void print() const;
    void printMemory() const;
    void serialization(const char* filename);
    void deserialization(const char* filename);
    size_t getMaxValue() const;
    size_t getMaxCount() const;
    void setMaxValue(int n);
    void setMaxCount(size_t k);
    MultiSet intersect(const MultiSet& other) const;
    MultiSet difference(const MultiSet& other) const;
    MultiSet complement() const;
};

#endif
