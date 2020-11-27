#include "Board.h"
#include "ui_Board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    BoardIcon.load(":/images/MainBoard");

    pieces.push_back(std::make_unique<Queen>(this,true));
    pieces.push_back(std::make_unique<Queen>(this));
    pieces.push_back(std::make_unique<Queen>(this,true));
    pieces.push_back(std::make_unique<Queen>(this,true));
    pieces.push_back(std::make_unique<Queen>(this,true));
    pieces.push_back(std::make_unique<Queen>(this,true));
    pieces.push_back(std::make_unique<Queen>(this,true));
    pieces.push_back(std::make_unique<Queen>(this,true));
    pieces.push_back(std::make_unique<Queen>(this,true));
    for (unsigned i=0;i<pieces.size();i++) {
        pieces[i]->move((i%8)*45+35,(i/8)*45+25);
    }
}
Board::~Board()
{
    delete ui;
}
void Board::paintEvent(QPaintEvent*){
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,width(),height(),BoardIcon);
    painter.end();
}

void Board::mousePressEvent(QMouseEvent* event){
    QPoint iMatrix,result;
    auto child = childAt(event->pos());
    if(child == nullptr)
    {
        qDebug()<<"No hay pieza\n";
        return;
    }
    qDebug()<<"Pieza Encontrada\n";
    qDebug()<<child->x()<<"\t"<<child->y()<<"\n";
    //Desactivar casillero
    result= {child->x(),child->y()};
    iMatrix=IndiceActual(result);
    tiles[iMatrix.x()][iMatrix.y()].SetContainPiece(false);
    qDebug()<<"La matriz "<<iMatrix.x()<<","<<iMatrix.y()
           <<tiles[iMatrix.x()][iMatrix.y()].GetContainPiece()<<"\n";
    //Marcar casillero actual
    pOrigin=QPoint{child->x(),child->y()};

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
            //Arrastrar ficha
            QByteArray data = event->mimeData()->data("application/x-dnditemdata");
            QDataStream dataStream(&data, QIODevice::ReadOnly);
            QPoint offset,result;
            dataStream>>offset;
            result=event->pos()-offset;
            pieces[0]->move(result);
            //qDebug()<<result.x()<<"\t"<<result.y()<<"\n";
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
        int iX=0,iY=0;
        QPoint offset,iMatrix,result;
        dataStream>>offset;
        result=event->pos() - offset;
        iMatrix=IndiceActual(result);
        iX=tiles[iMatrix.x()][iMatrix.y()].x+20;
        iY=tiles[iMatrix.x()][iMatrix.y()].y+40;
        if(iMatrix.x()!=-1&&iMatrix.y()!=-1)
        {
            pieces[0]->move(iX,iY);
            tiles[iMatrix.x()][iMatrix.y()].SetContainPiece(true);
        }
        else
            pieces[0]->move(result);
        if(event->source() == this){
           event->setDropAction(Qt::MoveAction);
           event->accept();
        }
        qDebug()<<"La matriz "<<iMatrix.x()<<","<<iMatrix.y()
               <<tiles[iMatrix.x()][iMatrix.y()].GetContainPiece()<<"\n";
    }
    qDebug()<<pieces[0]->x()<<"\t"<<pieces[0]->y()<<"\n";
}

QPoint Board::IndiceActual(const QPoint &p)
{
    QPoint indice{0,0};
    for(int i=0;i<8;++i)
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
