#ifndef KING_H
#define KING_H

#include "Piece.h"
class King : public Piece
{
public:
    King() = delete;
    explicit King(QWidget *parent = nullptr,bool color=false,QPoint position={0,0});
    ~King(){};
    void MovePiece()override;
};

#endif // KING_H
