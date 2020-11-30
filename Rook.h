#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
class Rook : public Piece
{
public:
    Rook() = delete;
    explicit Rook(QWidget *parent = nullptr,bool color=false,QPoint position={0,0});
    ~Rook(){};
    void MovePiece()override;
};

#endif // ROOK_H
