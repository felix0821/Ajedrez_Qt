#include "Tile.h"
Tile::Tile(){}
Tile::Tile(int x, int y)
{
    this->x=x;
    this->y=y;
}

uint8_t Tile::GetContainPiece()
{
    return containPiece;
}
void Tile::SetContainPiece(uint8_t contain)
{
    containPiece=contain;
}
int Tile::GetX()const
{
    return x;
}
int Tile::GetY()const
{
    return y;
}
