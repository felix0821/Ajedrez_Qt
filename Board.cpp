#include "Board.h"
#include "ui_Board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            int x=((i)*45)+15;
            int y=((j)*45)-15;
            tiles[i][j]=Tile(x,y);
        }
    }
    BoardIcon.load(":/images/MainBoard");
    //Queen q1,q2;
    //queenB2 = std::make_unique<Queen>(this);
    queenB1 = std::make_unique<Queen>(this);
    //queenB2->move(80,70);
    //queenB2->show();
    queenB1->move(35,160);
    queenB1->show();
}
//35,25-80,70 diff 45
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
        int xI,yI;
        QPoint offset,result,e;
        dataStream>>offset;
        e=event->pos() - offset;
        result=IndiceActual(e);
        xI=tiles[result.x()][result.y()].x+20;
        yI=tiles[result.x()][result.y()].y+35;
        if(result.x()!=-1&&result.y()!=-1)
            queenB1->move(xI,yI);
        else
            queenB1->move(event->pos() - offset);
        if(event->source() == this){
           event->setDropAction(Qt::MoveAction);
           event->accept();
        }
    }
    qDebug()<<queenB1->x()<<"\t"<<queenB1->y()<<"\n";
}

QPoint Board::IndiceActual(const QPoint &p)
{
    QPoint indice{0,0};
    int i;
    for(i=0;i<8;++i)
    {
        if(p.x()<tiles[i][0].x+tiles[i][0].w&&p.x()>=tiles[i][0].x)
        {
            indice.setX(i);
        }
        if(p.y()<tiles[0][i].y+tiles[0][i].h&&p.y()>=tiles[0][i].y)
        {
            indice.setY(i);
        }
    }
    return indice;
}
