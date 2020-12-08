#include "Piece.h"
#include "ui_Piece.h"

Piece::Piece(QWidget *parent) :
    QLabel(parent)
{
    ui->setupUi(this);
}
uint8_t Piece::GetId()const{
    return id;
}
bool Piece::GetColor()const
{
    return color;
}

QPoint Piece::GetPosition() const
{
    return position;
}
void Piece::SetPosition(const QPoint& point)
{
    position=point;
}
