#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
class Pawn : public Piece
{
public:
    Pawn() = delete;
    explicit Pawn(QWidget *parent = nullptr,bool color=false,QPoint position={0,0});
    ~Pawn(){};
    void MovePiece()override;
};

#endif // PAWN_H
