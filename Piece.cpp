#include "Piece.h"
#include "ui_Piece.h"

Piece::Piece(QWidget *parent) :
    QLabel(parent)
{
    ui->setupUi(this);
}
