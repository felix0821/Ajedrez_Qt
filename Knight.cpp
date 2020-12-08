#include "Knight.h"

Knight::Knight(QWidget* parent,bool color,QPoint position):
    Piece(parent)
{
    this->id=3;
    this->color= color;
    this->position=position;
    if(color)
    {
        icon.load(":/images/bKnight");
    }else
    {
        icon.load(":/images/wKnight");
    }
    this->setPixmap(icon.scaled(QSize(70,55),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Knight::MovePiece(){
}
