#include "Queen.h"

Queen::Queen(QWidget* parent,bool color):
    Piece(parent)
{
    this->color= color;
    if(color)
    {
        icon.load(":/images/bQueen");
    }else
    {
        icon.load(":/images/wQueen");
    }
    this->setPixmap(icon.scaled(QSize(60,40),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Queen::MovePiece(){
}
