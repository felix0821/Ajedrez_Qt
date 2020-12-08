#include "Bishop.h"

Bishop::Bishop(QWidget* parent,bool color,QPoint position):
    Piece(parent)
{
    this->id=4;
    this->color= color;
    this->position=position;
    if(color)
    {
        icon.load(":/images/bBishop");
    }else
    {
        icon.load(":/images/wBishop");
    }
    this->setPixmap(icon.scaled(QSize(70,55),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Bishop::MovePiece(){
}
