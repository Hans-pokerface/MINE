#include "define.h"
int RandomCreate(int);
int DeleteMine();

int DeleteMine()
{
    //delete the first existing mine in MineList
    //it's ok to just delete the first, caz it's randomly located
    for(int i=0;i<NUM;i++)
    {
        if(MineList[i].status==true)
        {
            MineList[i].status=false;
            return i;
        }
    }
    return -1;
}

int RandomCreate(int i)
{   
    //create a mine, index of which is i.
    MineList[i].posx=rand()%GRID_SIZE;
    MineList[i].posy=rand()%GRID_SIZE;

    for(int j=0;j<i;j++)
    {
        //check if there is repetition in the coordinate.
        if( MineList[j].status==true
            &&MineList[i].posx==MineList[j].posx
            &&MineList[i].posy==MineList[j].posy)
        {
            return 1;//exit with failure sign.
        }
    }    
    MineList[i].status=true;
    return 0;//exit with success sign.
}

void PrintMine()
{
    //for test. it will not occur in the game for players
    cout<<"  ";
    for(int i=1;i<=GRID_SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<GRID_SIZE;i++)
    {    
        cout<<(char)(i+'A')<<" ";
        for(int j=0;j<GRID_SIZE;j++)
        {
            if(MineGrid[i][j]==true)
                cout<<"1 ";                
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
}