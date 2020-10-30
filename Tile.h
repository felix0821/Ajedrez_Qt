#ifndef TILE_H
#define TILE_H
#include <memory>

#include "Piece.h"

class Tile
{
public:
    Tile();
    int x,y;
    uint16_t w,h;
private:
    std::unique_ptr<Piece> piece;
    bool containPiece;
};

#endif // TILE_H
