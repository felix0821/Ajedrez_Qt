#include "Matrix.h"

Matrix::Matrix()
{
    for(int i=0;i<ROW;i++)
    {
        std::vector <Tile> fogRow;
        for(int j=0;j<COL;j++)
        {
            int y=((i)*63)-25;
            int x=((j)*63)+10;
            fogRow.push_back(Tile(x,y));
        }
        Data.push_back(fogRow);
    }
}
const std::vector<Tile>& Matrix::operator[] (unsigned index)const
{
    return Data[index];
}
std::vector<Tile>& Matrix::operator[] (unsigned index){
    return Data[index];
}
