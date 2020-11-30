#include "Board.h"
#include "ui_Board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{   //QPoint index;
    ui->setupUi(this);
    setAcceptDrops(true);
    BoardIcon.load(":/images/MainBoard");
    initPieces();
}
void Board::initPieces(){
    int cD=coeficienteDistancia;
    //Creacion de fichas (referencia,color,posicion)
    pieces.push_back(std::make_unique<Rook>(this,true,QPoint{0,0}));
    pieces.push_back(std::make_unique<Knight>(this,true,QPoint{0,1}));
    pieces.push_back(std::make_unique<Bishop>(this,true,QPoint{0,2}));
    pieces.push_back(std::make_unique<Queen>(this,true,QPoint{0,3}));
    pieces.push_back(std::make_unique<King>(this,true,QPoint{0,4}));
    pieces.push_back(std::make_unique<Bishop>(this,true,QPoint{0,5}));
    pieces.push_back(std::make_unique<Knight>(this,true,QPoint{0,6}));
    pieces.push_back(std::make_unique<Rook>(this,true,QPoint{0,7}));
    for (int i=0;i<8;i++) {
        pieces.push_back(std::make_unique<Pawn>(this,true,QPoint{1,i}));
    }
    enemyPieces.push_back(std::make_unique<Rook>(this,false,QPoint{7,0}));
    enemyPieces.push_back(std::make_unique<Knight>(this,false,QPoint{7,1}));
    enemyPieces.push_back(std::make_unique<Bishop>(this,false,QPoint{7,2}));
    enemyPieces.push_back(std::make_unique<Queen>(this,false,QPoint{7,3}));
    enemyPieces.push_back(std::make_unique<King>(this,false,QPoint{7,4}));
    enemyPieces.push_back(std::make_unique<Bishop>(this,false,QPoint{7,5}));
    enemyPieces.push_back(std::make_unique<Knight>(this,false,QPoint{7,6}));
    enemyPieces.push_back(std::make_unique<Rook>(this,false,QPoint{7,7}));
    for (int i=0;i<8;i++) {
        enemyPieces.push_back(std::make_unique<Pawn>(this,false,QPoint{6,i}));
    }
    //Posicionar fichas
    for (unsigned i=0;i<pieces.size();i++) {
        int iX=pieces[i]->GetPosition().x();
        int iY=pieces[i]->GetPosition().y();
        tiles[iX][iY].SetContainPiece(true);
        pieces[i]->move(tiles[iX][iY].GetX()+cD,
                tiles[iX][iY].GetY()+(2*cD));
    }
    for (unsigned i=0;i<enemyPieces.size();i++) {
        int iX=enemyPieces[i]->GetPosition().x();
        int iY=enemyPieces[i]->GetPosition().y();
        tiles[iX][iY].SetContainPiece(true);
        enemyPieces[i]->move(tiles[iX][iY].GetX()+cD,tiles[iX][iY].GetY()+(2*cD));
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
    QPoint result;
    auto child = childAt(event->pos());
    selectionPiece= static_cast<Piece*>(childAt(event->pos()));
    //qDebug()<<selectionPiece->GetColor()<<"\n";
    if(child == nullptr)
    {
        qDebug()<<"No hay pieza\n";
        return;
    }
    qDebug()<<"Pieza Encontrada\n";
    qDebug()<<child->x()<<"\t"<<child->y()<<"\n";
    //Desactivar casillero
    result= {child->x(),child->y()};
    mOrigin=IndiceActual(result);
    tiles[mOrigin.x()][mOrigin.y()].SetContainPiece(false);
    qDebug()<<"La matriz "<<mOrigin.x()<<","<<mOrigin.y()
           <<tiles[mOrigin.x()][mOrigin.y()].GetContainPiece()<<"\n";
    //Marcar casillero actual
    pOrigin=QPoint{child->x(),child->y()};
    //Invocar funciones de Drag and Drop
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
            selectionPiece->move(result);

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
        QPoint offset,iM,result;
        dataStream>>offset;
        result=event->pos() - offset;
        iM=IndiceActual(result);
        iX=tiles[iM.x()][iM.y()].GetX()+20;
        iY=tiles[iM.x()][iM.y()].GetY()+40;
        if(!tiles[iM.x()][iM.y()].GetContainPiece())
        {
            selectionPiece->move(iX,iY);
            tiles[iM.x()][iM.y()].SetContainPiece(true);
        }
        else
        {
            tiles[mOrigin.x()][mOrigin.y()].SetContainPiece(true);
            selectionPiece->move(pOrigin);
            //selectionPiece->move(result);
        }
        if(event->source() == this){
           event->setDropAction(Qt::MoveAction);
           event->accept();
        }
        qDebug()<<"La matriz "<<iM.x()<<","<<iM.y()
               <<tiles[iM.x()][iM.y()].GetContainPiece()<<"\n";
    }
    qDebug()<<selectionPiece->x()<<"\t"<<selectionPiece->y()<<"\n\n";
}

QPoint Board::IndiceActual(const QPoint &p)
{
    QPoint indice{0,0};
    uint8_t lim=0;
    for(int i=0;i<8;++i)
    {
        if(p.x()<tiles[0][i].GetX()+tiles[0][i].w&&p.x()>=tiles[0][i].GetX())
        {
            indice.setY(i);
            ++lim;
        }
        if(p.y()<tiles[i][0].GetY()+tiles[i][0].h&&p.y()>=tiles[i][0].GetY())
        {
            indice.setX(i);
            ++lim;
        }
        if(lim==2)break;
    }
    return indice;
}
