#include "define.h"
int RandomCreate(int,int);
int DeleteMine();

int DeleteMine()
{
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

int RandomCreate(int i,int num)
{   
    //create a mine, index of which is i.
    MineList[i].posx=rand()%7;
    MineList[i].posy=rand()%7;

    if(MineList[i].posx==GRID_SIZE/2&&MineList[i].posy==GRID_SIZE/2)
        return 1;

    for(int j=0;j<num;j++)
    {
        //check if there is repetition in the coordinate.
        if(j!=i&&MineList[j].status==true
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
    cout<<"  ";
    for(int i=1;i<=GRID_SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<GRID_SIZE;i++)
    {    
        cout<<(char)(i+'A')<<" ";
        for(int j=0;j<GRID_SIZE;j++)
        {
            if(i==GRID_SIZE/2&&j==GRID_SIZE/2)
            {
                cout<<"? ";
            }
            else
            {
                if(MineGrid[i][j].occupied==true)
                {
                    char s=MineGrid[i][j].index+'A';
                    cout<<s<<' ';   
                }             
                else
                    cout<<"0 ";
            }
        }
        cout<<endl;
    }
}