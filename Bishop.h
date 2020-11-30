#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop() = delete;
    explicit Bishop(QWidget *parent = nullptr,bool color=false,QPoint position={0,0});
    ~Bishop(){};
    void MovePiece()override;
};

#endif // BISHOP_H
