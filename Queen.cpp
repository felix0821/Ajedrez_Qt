#include "Queen.h"

Queen::Queen(QWidget* parent,bool color,QPoint position):
    Piece(parent)
{
    this->id=5;
    this->color= color;
    this->position=position;
    if(color)
    {
        icon.load(":/images/bQueen");
    }else
    {
        icon.load(":/images/wQueen");
    }
    this->setPixmap(icon.scaled(QSize(70,55),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Queen::MovePiece(){
}
