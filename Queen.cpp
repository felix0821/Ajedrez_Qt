#include "Queen.h"

Queen::Queen(QWidget* parent):
    Piece(parent)
{
    icon.load(":/images/bQueen");
    this->setPixmap(icon.scaled(QSize(50,50),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Queen::MovePiece(){
}
