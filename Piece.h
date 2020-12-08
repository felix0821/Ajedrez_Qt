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
    virtual bool GetColor()const;
    virtual uint8_t GetId()const;
    virtual QPoint GetPosition()const;
    virtual void SetPosition(const QPoint&);
private:
    Ui::Piece *ui;
protected:
    QPixmap icon{};
    uint8_t id{0};
    bool color{0}; // 0 for black, 1 for white
    QPoint position{0,0};
};

#endif // PIECE_H
