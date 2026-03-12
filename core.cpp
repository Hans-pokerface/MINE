#include <bits/stdc++.h>
using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

const int INF=0x3f3f3f3f;const int MAXN=200;
const int SIZE=7;const int NUM=12;

/*---definition of struct---*/
typedef struct
{
    bool status;//true--in grid; false--out of grid
    int posx;//[0,6]
    int posy;//[0,6]
} MineInfo;
MineInfo MineList[MAXN];

typedef struct
{
    bool occupied;//true--mine in palce; false--no mine
    int index;//if occupied, record which mine is there
}GridInfo;
GridInfo MineGrid[SIZE][SIZE];

char PlayerOp[SIZE][SIZE];

/*---declaration of functions---*/
void ClearGrid();
void PrintGrid();
void RecordInGrid();
int RandomCreate(int);
void RandomMove();


/*---implement of functions---*/
void ClearGrid()
{
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            MineGrid[i][j].occupied=false;
}

void PrintGrid()
{
    cout<<"  ";
    for(int i=1;i<=SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<SIZE;i++)
    {    
        cout<<i+1<<" ";
        for(int j=0;j<SIZE;j++)
        {
            cout<<PlayerOp[i][j]<<' ';
        }
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
        if(MineGrid[x][y].occupied==false)
        {
            MineGrid[x][y].occupied=true;
            MineGrid[x][y].index=i;
        }
        else
        {
            int rst=MineGrid[x][y].index;
            MineGrid[x][y].occupied==false;

            RandomCreate(rst); 
            x=MineList[rst].posx;
            y=MineList[rst].posy;
            MineGrid[x][y].occupied=true;
            MineGrid[x][y].index=rst;

            RandomCreate(i);
            x=MineList[i].posx;
            y=MineList[i].posy;
            MineGrid[x][y].occupied=true;
            MineGrid[x][y].index=i;
        }
    }
}

int RandomCreate(int i)
{   
    //create a mine, index of which is i.
    MineList[i].posx=rand()%7;
    MineList[i].posy=rand()%7;
    for(int j=0;j<NUM;j++)
    {
        //check if there is repetition in the coordinate.
        if(j!=i&&MineList[j].status==true
               &&MineList[i].posx==MineList[j].posx
               &&MineList[i].posy==MineList[j].posy)
        {
            return 0;//exit with failure sign.
        }
    }
    MineList[i].status=true;
    return 1;//exit with success sign.
}

void RandomMove()
{
    for(int i=0;i<NUM;i++)
    {
        //randomly decide which direction to go.
        int Dir=rand()%4;
        if(MineList[i].status==false)
            continue;
        switch (Dir){
            case 0:
                MineList[i].posx++;
                //check if the mine is still in the grid.
                if(MineList[i].posx>=SIZE||MineList[i].posx==SIZE/2)
                    MineList[i].status=false;                 
                break;
            case 1:
                MineList[i].posx--;
                if(MineList[i].posx<0||MineList[i].posx==SIZE/2)
                    MineList[i].status=false;
                break;
            case 2:
                MineList[i].posy++;
                if(MineList[i].posy>=SIZE||MineList[i].posy==SIZE/2)
                    MineList[i].status=false;
                break;
            case 3:
                MineList[i].posy--;
                if(MineList[i].posy<0||MineList[i].posy==SIZE/2)
                    MineList[i].status=false;
                break;
            default:
                break;
        }
    }
}

int main() 
{
    srand((unsigned)time(NULL));//do not use it in the loop

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
        {
            if(i==SIZE/2&&j==SIZE/2)
                PlayerOp[i][j]='?';
            else
                PlayerOp[i][j]='o';
        }
    PrintGrid();

    ClearGrid();
    for(int i=0;i<NUM;i++)
    {
        int res=RandomCreate(i);
        if(!res) i--;
    }
    RecordInGrid();


    /*--testcode--
    for(int i=0;i<NUM;i++)
        cout<<current[i].posx<<' '<<current[i].posy<<endl;
    */

    while(1)
    {
        int PlayerX,PlayerY;
        cin>>PlayerX>>PlayerY;
        PlayerX--; PlayerY--;
        if(MineGrid[PlayerX][PlayerY].occupied==true)
        {
            PlayerOp[PlayerX][PlayerY]='x';
            PrintGrid();
            cout<<"LOSE";
        }
        else
        {
            PlayerOp[PlayerX][PlayerY]='+';
            PrintGrid();
            ClearGrid();
            RandomMove();
            RecordInGrid();
        }
    }
}