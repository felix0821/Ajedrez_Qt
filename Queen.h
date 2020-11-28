#ifndef QUEEN_H
#define QUEEN_H

#include <QDebug>
#include <QWidget>
#include <QLabel>
#include "Piece.h"

class Queen : public Piece
{
public:
    Queen() = delete;
    explicit Queen(QWidget *parent = nullptr,bool color=false,QPoint position={0,0});
    ~Queen(){};
    void MovePiece()override;
};

#endif // QUEEN_H
