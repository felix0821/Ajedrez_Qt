#include "Tile.h"

Tile::Tile(){}
Tile::Tile(int x, int y)
{
    this->x=x;
    this->y=y;
}

bool Tile::GetContainPiece()
{
    return containPiece;
}
void Tile::SetContainPiece(bool contain)
{
    containPiece=contain;
}
