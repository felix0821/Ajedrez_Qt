#include "Queen.h"

Queen::Queen(QWidget* parent):
    Piece(parent)
{
    icon.load(":/images/bQueen");
    this->setPixmap(icon.scaled(QSize(60,40),Qt::KeepAspectRatio));
    this->adjustSize();
}
void Queen::MovePiece(){
}
