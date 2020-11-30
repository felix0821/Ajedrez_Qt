#include "King.h"

King::King(QWidget* parent,bool color,QPoint position):
    Piece(parent)
{
    this->color= color;
    this->position=position;
    if(color)
    {
        icon.load(":/images/bKing");
    }else
    {
        icon.load(":/images/wKing");
    }
    this->setPixmap(icon.scaled(QSize(60,40),Qt::KeepAspectRatio));
    this->adjustSize();
}
void King::MovePiece(){
}
