#include "define.h"
void ClearGrid();
void PrintGrid();
void RecordInGrid();

void ClearGrid()
{
    //initialize MineGrid: each grid is false, meaning empty
    for(int i=0;i<GRID_SIZE;i++)
        for(int j=0;j<GRID_SIZE;j++)
            MineGrid[i][j]=false;
}

void PrintGrid()
{
    //print player's option, showing which grid has been chosen
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
    //record which grid has a mine according to MineList info
    ClearGrid();
    for(int i=0;i<NUM;i++)
    {
        if(MineList[i].status==false)
            continue;
        
        int x=MineList[i].posx;
        int y=MineList[i].posy;
        MineGrid[x][y]=true;
    }
}