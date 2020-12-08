#include "Pawn.h"

Pawn::Pawn(QWidget* parent,bool color,QPoint position):
    Piece(parent)
{
    this->id=1;
    this->color= color;
    this->position=position;
    if(color)
    {
        icon.load(":/images/bPawn");
    }else
    {
        icon.load(":/images/wPawn");
    }
    this->setPixmap(icon.scaled(QSize(50,55),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Pawn::MovePiece(){
}
