#include "Rook.h"

Rook::Rook(QWidget* parent,bool color,QPoint position):
    Piece(parent)
{
    this->id=2;
    this->color= color;
    this->position=position;
    if(color)
    {
        icon.load(":/images/bRook");
    }else
    {
        icon.load(":/images/wRook");
    }
    this->setPixmap(icon.scaled(QSize(70,55),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Rook::MovePiece(){
}
