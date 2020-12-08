#ifndef TILE_H
#define TILE_H
#include <memory>

#include "Piece.h"

class Tile
{
public:
    Tile();
    Tile(int,int);

    uint16_t w{63},h{63};
    uint8_t GetContainPiece();
    void SetContainPiece(uint8_t);
    int GetX()const;
    int GetY()const;
private:
    std::shared_ptr<Piece> piece=nullptr;
    uint8_t containPiece{0};
    int x{0},y{0};
};

#endif // TILE_H
