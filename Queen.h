#ifndef QUEEN_H
#define QUEEN_H

#include <QDebug>

#include "Piece.h"

class Queen : public Piece
{
public:
    Queen() = delete;
    explicit Queen(QWidget *parent = nullptr,bool color=false);
    ~Queen(){};
    void MovePiece();
};

#endif // QUEEN_H
