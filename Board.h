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

#include "Queen.h"
#include "Piece.h"

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
    Ui::Board *ui;
    QPixmap BoardIcon;
    std::unique_ptr<Piece> queen;
    void mousePressEvent(QMouseEvent*) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif // BOARD_H
