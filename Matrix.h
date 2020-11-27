#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "Array.h"

class Matrix
{
private:
    std::vector<Array>Data{0,Array{0}};
public:
    Matrix()=delete;
    Matrix(const std::size_t x,const std::size_t y);
    ~Matrix(){}
    std::size_t getSize()const;
    const Array& operator[] (unsigned index)const;
    Array& operator[] (unsigned index);
};

#endif // MATRIX_H
