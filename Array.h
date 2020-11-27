#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <vector>
#include "Tile.h"
class Array
{
private:
    std::vector<Tile> Data{};

public:
    Array()=delete;
    Array(const std::size_t size);
    ~Array(){};
    std::size_t getSize()const;
    const Tile& operator[] (unsigned index) const;
    Tile& operator[] (unsigned index);

};

#endif // ARRAY_H
