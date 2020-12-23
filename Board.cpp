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
    int cD=COEF_DIST;
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
        tiles[iX][iY].SetContainPiece(1);
        pieces[i]->move(tiles[iX][iY].GetX()+cD,
                tiles[iX][iY].GetY()+(2*cD));
    }
    for (unsigned i=0;i<enemyPieces.size();i++) {
        int iX=enemyPieces[i]->GetPosition().x();
        int iY=enemyPieces[i]->GetPosition().y();
        tiles[iX][iY].SetContainPiece(2);
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
    QPixmap Signal{},D;
    Signal.load(":/images/Destello");
    //QPixmap pixmapVal = signs[0]->pixmap(Qt::ReturnByValue);
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
    CreateSignal();
    //MoveCondition(selectionPiece,signs,this);
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
        QPoint offset,iM,result;
        //Movimiento
        dataStream>>offset;
        result=event->pos() - offset;
        iM=IndiceActual(result);
        pieceMove(iM);
        //Reiniciar señalizaciones
        signs.clear();
        indexSigns.clear();
        if(event->source() == this){
           event->setDropAction(Qt::MoveAction);
           event->accept();
        }
    }
    qDebug()<<selectionPiece->x()<<"\t"<<selectionPiece->y()<<"\n\n";
}
//Metodo que permite el movimiento de la ficha
void Board::pieceMove(const QPoint &iM)
{
    int cD=COEF_DIST;
    int iX=0,iY=0;
    bool validMove=false;
    iX=tiles[iM.x()][iM.y()].GetX()+cD;
    iY=tiles[iM.x()][iM.y()].GetY()+(2*cD);
    //Verioficar movimiento valido
    for(unsigned i=0;i<indexSigns.size();++i)
    {
        if(indexSigns[i]==iM) validMove=true;
    }
    //tiles[iM.x()][iM.y()].GetContainPiece()==0
    if(validMove)
    {
        uint8_t contain=tiles[iM.x()][iM.y()].GetContainPiece();
        if(contain!=0){
            if(contain==1)
                for_each(pieces.begin(), pieces.end(),
                              [=](std::unique_ptr<Piece> &n) { if(n!=NULL&&n->GetPosition()==iM)n=NULL; });
            if(contain==2)
                for_each(enemyPieces.begin(), enemyPieces.end(),
                              [=](std::unique_ptr<Piece> &n) { if(n!=NULL&&n->GetPosition()==iM)n=NULL; });
        }
        selectionPiece->SetPosition(QPoint{iM});
        selectionPiece->move(iX,iY);
        tiles[iM.x()][iM.y()].SetContainPiece(selectionPiece->GetColor()?1:2);
        //Mostrar mov
        qDebug()<<"La matriz "<<iM.x()<<","<<iM.y()
               <<tiles[iM.x()][iM.y()].GetContainPiece()<<"\n";
    }
    else
    {
        tiles[mOrigin.x()][mOrigin.y()].SetContainPiece(selectionPiece->GetColor()?1:2);
        selectionPiece->move(pOrigin);
        qDebug()<<"La matriz "<<mOrigin.x()<<","<<mOrigin.y()
               <<tiles[mOrigin.x()][mOrigin.y()].GetContainPiece()<<"\n";
    }
}
//Indica la posicion de la casilla segun la coordenada
QPoint Board::IndiceActual(const QPoint &p)
{
    QPoint index{0,0};
    uint8_t lim=0;
    for(int i=0;i<8;++i)
    {
        if(p.x()<tiles[0][i].GetX()+tiles[0][i].w&&p.x()>=tiles[0][i].GetX())
        {
            index.setY(i);
            ++lim;
        }
        if(p.y()<tiles[i][0].GetY()+tiles[i][0].h&&p.y()>=tiles[i][0].GetY())
        {
            index.setX(i);
            ++lim;
        }
        if(lim==2)break;
    }
    return index;
}
//Crea las señalizaciones de la ficha
void Board::CreateSignal()
{
    //qDebug()<<selectionPiece->GetPosition()<<"\n";
    indexSigns=AnalyzeMove();
    QPixmap Signal{":/images/Destello"};
    for(unsigned i=0;i<indexSigns.size();++i)
    {
        int iX=indexSigns[i].x();
        int iY=indexSigns[i].y();
        signs.push_back(std::make_unique<QLabel>(this));
        signs[i]->setPixmap(Signal.scaled(QSize(80,80),Qt::KeepAspectRatio));
        signs[i]->adjustSize();
        signs[i]->show();
        signs[i]->move(tiles[iX][iY].GetX(),tiles[iX][iY].GetY()+35);
    }
    //qDebug()<<indexSigns.size()<<"\n";
}
//Analiza el movimiento de la ficha segun su id
std::vector<QPoint> Board::AnalyzeMove()
{   //s:selectionPiece
    int sX=selectionPiece->GetPosition().x();
    int sY=selectionPiece->GetPosition().y();
    std::vector<QPoint>tempIndex;
    uint8_t id=selectionPiece->GetId();
    switch (id) {
    case 1:
        AnalyzePawn(tempIndex,sX,sY);
        break;
    case 2:
        AnalyzeRook(tempIndex,sX,sY);
        break;
    }
    return tempIndex;
}
//Analiza los posibles movimeintos del peon
void Board::AnalyzePawn(std::vector<QPoint>&tempIndex,const int&x,const int&y)
{
    int abscissa,ordinate,sign;
    uint8_t team,verify;
    //Verificar la recta vertical y numero de movs
    if(selectionPiece->GetColor()){
        sign=1;
        if(x==7) return;
        abscissa= x==1? 2:1;
    }
    else {
        sign=-1;
        if(x==0) return;
        abscissa=selectionPiece->GetPosition().x()==6? 2:1;
    }
    //Agregar señalizaciones hacia adelante
    for(int i=0;i<abscissa;++i)
    {
        int xT=x+((i+1)*sign);
        if(!tiles[xT][y].GetContainPiece())
            tempIndex.push_back(QPoint{xT,y});
        else break;
    }
    //Agrega señalizaciones de comida
    abscissa=x+(1*sign);
    team=selectionPiece->GetColor()?1:2;
    switch (y) {
    case 0:
        ordinate=y+1;
        verify=tiles[abscissa][ordinate].GetContainPiece();
        if(verify!=0&&verify!=team)
            tempIndex.push_back(QPoint{abscissa,ordinate});
        break;
    case 7:
        ordinate=y-1;
        verify=tiles[abscissa][ordinate].GetContainPiece();
        if(verify!=0&&verify!=team)
            tempIndex.push_back(QPoint{abscissa,ordinate});
        break;
    default:
        ordinate=y+1;
        verify=tiles[abscissa][ordinate].GetContainPiece();
        if(verify!=0&&verify!=team)
            tempIndex.push_back(QPoint{abscissa,ordinate});
        ordinate=y-1;
        verify=tiles[abscissa][ordinate].GetContainPiece();
        if(verify!=0&&verify!=team)
            tempIndex.push_back(QPoint{abscissa,ordinate});
        return;
    }
}

void Board::AnalyzeRook(std::vector<QPoint>&tempIndex,const int&x,const int&y)
{
    int verifyP,verifyN;
    //los closes son condiciones de bloqueo segun fichas
    //los verifys son verificadores en ambos sentidos
    uint8_t team,closeP{1},closeN{1};
    team=selectionPiece->GetColor()?1:2;
    int i=1;
    while((closeP==1||closeN==1)&&i<7){
        verifyP=-1;verifyN=-1;
        if(y+i<8&&y+i>-1&&closeP==1)verifyP=tiles[x][y+i].GetContainPiece();
        if(y-i<8&&y-i>-1&&closeN==1)verifyN=tiles[x][y-i].GetContainPiece();
        if(verifyP!=-1&&verifyP!=team){
            tempIndex.push_back(QPoint{x,y+i});
        }
        if(verifyP!=0)closeP=0;
        if(verifyN!=-1&&verifyN!=team){
            tempIndex.push_back(QPoint{x,y-i});
        }
        if(verifyN!=0)closeN=0;
        if(verifyP==-1&&verifyN==-1){closeP=0;closeN=0;}
        i++;
    }
    i=1;closeP=1;closeN=1;
    while((closeP==1||closeN==1)&&i<7){
        verifyP=-1;verifyN=-1;
        if(x+i<8&&x+i>-1&&closeP==1)verifyP=tiles[x+i][y].GetContainPiece();
        if(x-i<8&&x-i>-1&&closeN==1)verifyN=tiles[x-i][y].GetContainPiece();
        if(verifyP!=-1&&verifyP!=team){
            tempIndex.push_back(QPoint{x+i,y});
        }
        if(verifyP!=0)closeP=0;
        if(verifyN!=-1&&verifyN!=team){
            tempIndex.push_back(QPoint{x-i,y});
        }
        if(verifyN!=0)closeN=0;
        if(verifyP==-1&&verifyN==-1){closeP=0;closeN=0;}
        i++;
    }
}
