#ifndef TILE_H
#define TILE_H
#include <memory>

#include "Piece.h"

class Tile
{
public:
    Tile();
    Tile(int,int);
    int x{0},y{0};
    uint16_t w{45},h{45};
    bool GetContainPiece();
    void SetContainPiece(bool);
private:
    //std::unique_ptr<Piece> piece;
    bool containPiece;
};

#endif // TILE_H
