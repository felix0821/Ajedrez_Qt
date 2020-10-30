#include "Board.h"
#include "ui_Board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    BoardIcon.load(":/images/MainBoard");
    queen = std::make_unique<Queen>(this);
    queen->move(20,20);
    queen->show();
}

Board::~Board()
{
    delete ui;
}
void Board::paintEvent(QPaintEvent*){
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,width(),height(),BoardIcon);
    //painter.drawTiledPixmap(0,0,width(),height(),BoardIcon);
    painter.end();
}

void Board::mousePressEvent(QMouseEvent* event){
    auto child = childAt(event->pos());
    if(child == nullptr)
    {
        qDebug()<<"null\n";
        return;
    }
    qDebug()<<"child enc\n";
    QByteArray data;
    QDataStream dataStream(&data, QIODevice::WriteOnly);
    dataStream<<QPoint(event->pos()-child->pos());

    QMimeData* mimeData = new QMimeData();
    mimeData->setData("application/x-dnditemdata", data);
    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::CopyAction|Qt::MoveAction,Qt::CopyAction);
}
void Board::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}
void Board::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}
void Board::dropEvent(QDropEvent* event){
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray data = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&data, QIODevice::ReadOnly);

        QPoint offset;
        dataStream>>offset;
        queen->move(event->pos() - offset);
        if(event->source() == this){
           event->setDropAction(Qt::MoveAction);
           event->accept();
        }
    }
    qDebug()<<queen->x()<<"\t"<<queen->y()<<"\n";
}
