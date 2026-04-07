#include "define.h"
void ClearGrid();
void PrintGrid();
void RecordInGrid();

void ClearGrid()
{
    for(int i=0;i<GRID_SIZE;i++)
        for(int j=0;j<GRID_SIZE;j++)
            MineGrid[i][j].occupied=false;
}

void PrintGrid()
{
    cout<<"  ";
    for(int i=1;i<=GRID_SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<GRID_SIZE;i++)
    {    
        cout<<(char)(i+'A')<<" ";
        for(int j=0;j<GRID_SIZE;j++)
            cout<<PlayerOp[i][j]<<' ';
        cout<<endl;
    }
}

void RecordInGrid() 
{
    ClearGrid();
    for(int i=0;i<NUM;i++)
    {
        if(MineList[i].status==false)
            continue;
        
        int x=MineList[i].posx;
        int y=MineList[i].posy;
        MineGrid[x][y].occupied=true;
        MineGrid[x][y].index=i;
    }
}