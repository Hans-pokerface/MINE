#include "define.h"

void EndofGame();
void Failure(int,int);

void EndofGame()
{
    //display when the player wins.
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
            {
                cout << "\033[31m" << "● " << "\033[0m";//mines
            }             
            else
            {
                if(PlayerOp[i][j]=='+')
                    cout<<"\033[1;34m"<<PlayerOp[i][j]<<' '<<"\033[0m";
                    //the places the player chose
                else
                    cout<<PlayerOp[i][j]<<' ';
            }
        }
        cout<<endl;
    }
}

void Failure(int x,int y)
{
    //display when the player fails in the process
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
                cout << "\033[31m" << "x " << "\033[0m";//failure pos
            }
            else
            {
                if(MineGrid[i][j]==true)
                {
                    cout << "\033[31m" << "● " << "\033[0m";//other mines
                }             
                else
                    cout<<PlayerOp[i][j]<<' ';
            }
        }
        cout<<endl;
    }
}