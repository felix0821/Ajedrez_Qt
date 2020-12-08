#include "King.h"

King::King(QWidget* parent,bool color,QPoint position):
    Piece(parent)
{
    this->id=6;
    this->color= color;
    this->position=position;
    if(color)
    {
        icon.load(":/images/bKing");
    }else
    {
        icon.load(":/images/wKing");
    }
    this->setPixmap(icon.scaled(QSize(70,55),Qt::KeepAspectRatio));
    this->adjustSize();
}
void King::MovePiece(){
}
