#ifndef PIECE_H
#define PIECE_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class Piece;
}

class Piece : public QLabel
{
    Q_OBJECT

public:
    explicit Piece(QWidget *parent = nullptr);
    virtual ~Piece(){};
    virtual void MovePiece() = 0;
private:
    Ui::Piece *ui;
protected:
    QPixmap icon{};
    bool color = 0; // 0 for black, 1 for white
};

#endif // PIECE_H
