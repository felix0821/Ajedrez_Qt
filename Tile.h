#ifndef TILE_H
#define TILE_H
#include <memory>

#include "Piece.h"

class Tile
{
public:
    Tile();
    Tile(int,int);

    uint16_t w{45},h{45};
    bool GetContainPiece();
    void SetContainPiece(bool);
    int GetX()const;
    int GetY()const;
private:
    std::shared_ptr<Piece> piece=nullptr;
    bool containPiece;
    int x{0},y{0};
};

#endif // TILE_H
