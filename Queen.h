#ifndef QUEEN_H
#define QUEEN_H

#include <QDebug>

#include "Piece.h"

class Queen : public Piece
{
public:
    explicit Queen(QWidget *parent = nullptr);
    ~Queen(){};
    void MovePiece();
};

#endif // QUEEN_H
