#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "Tile.h"
#define ROW 8
#define COL 8
class Matrix
{
private:
    std::vector<std::vector<Tile>> Data;
public:
    Matrix();
    ~Matrix(){};
    std::size_t getSize()const;
    const std::vector<Tile>& operator[] (unsigned index)const;
    std::vector<Tile>& operator[] (unsigned index);
};

#endif // MATRIX_H
