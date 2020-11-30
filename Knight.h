#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
class Knight : public Piece
{
public:
    Knight() = delete;
    explicit Knight(QWidget *parent = nullptr,bool color=false,QPoint position={0,0});
    ~Knight(){};
    void MovePiece()override;
};

#endif // KNIGHT_H
