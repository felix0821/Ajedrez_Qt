#include "Matrix.h"

Matrix::Matrix(const std::size_t x,const std::size_t y)
{
    Data=std::vector<Array>(x, Array{y});
}
std::size_t Matrix::getSize()const
{
    return Data.size();
}
const Array& Matrix::operator[] (unsigned index)const
{
    return Data[index];
}
Array& Matrix::operator[] (unsigned index)
{
    return Data[index];
}
