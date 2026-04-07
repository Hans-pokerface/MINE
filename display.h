#include "define.h"

void EndofGame();
void Failure(int,int);

void EndofGame()
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
            if(MineGrid[i][j].occupied==true)
            {
                cout << "\033[31m" << "● " << "\033[0m";
            }             
            else
            {
                if(PlayerOp[i][j]=='+')
                    cout<<"\033[1;34m"<<PlayerOp[i][j]<<' '<<"\033[0m";
                else
                    cout<<PlayerOp[i][j]<<' ';
            }
        }
        cout<<endl;
    }
}

void Failure(int x,int y)
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
            if(i==x&&j==y)
            {
                cout << "\033[31m" << "X " << "\033[0m";
            }
            else
            {
                if(MineGrid[i][j].occupied==true)
                {
                    cout << "\033[31m" << "● " << "\033[0m";
                }             
                else
                    cout<<PlayerOp[i][j]<<' ';
            }
        }
        cout<<endl;
    }
}