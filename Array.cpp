#include "Array.h"

Array::Array(const std::size_t size)
{
    Data=std::vector<Tile>(size);;
}

std::size_t Array::getSize()const
{
    return Data.size();
}
const Tile& Array::operator[] (unsigned index) const
{
    return Data[index];
}

Tile& Array::operator[] (unsigned index)
{
    return Data[index];
}
