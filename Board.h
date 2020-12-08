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

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Piece.h"
#include "Matrix.h"

#define COEF_DIST 25
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
    std::vector<std::unique_ptr<QLabel>>signs;
    std::vector<std::unique_ptr<Piece>>pieces;
    std::vector<std::unique_ptr<Piece>>enemyPieces;
    std::vector<QPoint>indexSigns;
    Matrix tiles;
    QPoint pOrigin,mOrigin;
    Piece *selectionPiece;
    //funciones privadas
    void initPieces();
    //funciones de evento
    void mousePressEvent(QMouseEvent*) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent* event) override;
    //metodos complemento
    void pieceMove(const QPoint&);
    QPoint IndiceActual(const QPoint &p);
    //metodos de funcionalidad
    void CreateSignal();
    std::vector<QPoint> AnalyzeMove();
    void AnalyzePawn(std::vector<QPoint>&tempIndex,const int&x,const int&y);
};

#endif // BOARD_H
