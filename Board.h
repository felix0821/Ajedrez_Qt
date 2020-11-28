#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QMimeData>
#include <QDrag>
#include <QDebug>
#include <memory>
#include <iostream>

#include <vector>
#include "Queen.h"
#include "Piece.h"
#include "Matrix.h"

#define coeficienteDistancia 20;
namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();
    void paintEvent(QPaintEvent*) override;

private:
    //variables privadas
    Ui::Board *ui;
    QPixmap BoardIcon;
    std::vector<std::unique_ptr<Piece>>pieces;
    Matrix tiles;
    QPoint pOrigin,mOrigin;
    Piece *selectionPiece;
    //funciones privadas
    //funciones de evento
    void mousePressEvent(QMouseEvent*) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent* event) override;
    //funciones complemento
    QPoint IndiceActual(const QPoint &p);
};

#endif // BOARD_H
